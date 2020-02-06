/*
 * Player.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: laghy
 */

#include "Player.h"

Player::Player() {
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
	anima = 0;
	hit = 0;
	inv = false;
	gRender = NULL;
	corrani = 0;
	mCollider.x = 0;
	mCollider.y = 0;
	mCollider.h = 0;
	mCollider.w = 0;
	life = 3;
	key = false;
	map = false;
	checkmate = false;
}

Player::Player ( SDL_Renderer * r , LTexture* Pt,int posx , int posy){
	//Initialize the offsets
	mPosX = posx;
	mPosY = posy;
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
	//initialize render
	gRender = r;
	anima = 0;
	hit = 0;
	inv = false;
	//load texture
	texture = *Pt;
	life = 3;
	key = false;
	map = false;
	checkmate = false;
	int segm = 15;
	//up
	rect[UP].x = segm * 4;
	rect[UP].y = 0;
	rect[UP].w = segm;
	rect[UP].h = segm;

	rect[UP1].x = segm * 4;
	rect[UP1].y = segm * 2;
	rect[UP1].w = segm;
	rect[UP1].h = segm;

	rect[DOWN].x = 0;
	rect[DOWN].y = 0;
	rect[DOWN].w = segm;
	rect[DOWN].h = segm;

	rect[DOWN1].x = 0;
	rect[DOWN1].y = segm * 2;
	rect[DOWN1].w = segm;
	rect[DOWN1].h = segm;

	rect[LEFT].x = segm * 2;
	rect[LEFT].y = 0;
	rect[LEFT].w = segm;
	rect[LEFT].h = segm;

	rect[LEFT1].x = segm * 2;
	rect[LEFT1].y = segm * 2;
	rect[LEFT1].w = segm;
	rect[LEFT1].h = segm;

	rect[RIGHT].x = segm * 6;
	rect[RIGHT].y = 0;
	rect[RIGHT].w = segm;
	rect[RIGHT].h = segm;

	rect[RIGHT1].x = segm * 6;
	rect[RIGHT1].y = segm * 2;
	rect[RIGHT1].w = segm;
	rect[RIGHT1].h = segm;

	rect[LSWORD].x = 24;
	rect[LSWORD].y = 90;
	rect[LSWORD].h = segm;
	rect[LSWORD].w = 27;

	rect[RSWORD].x = 84;
	rect[RSWORD].y = 90;
	rect[RSWORD].h = segm;
	rect[RSWORD].w = 27;

	rect[DSWORD].x = 0;
	rect[DSWORD].y = 84;
	rect[DSWORD].w = segm;
	rect[DSWORD].h = 27;

	rect[USWORD].x = 60;
	rect[USWORD].y = 84;
	rect[USWORD].w = segm;
	rect[USWORD].h = 27;

	corrani = 0;

	mCollider.w = P_WIDTH;
	mCollider.h = P_HEIGHT;
}

Player::~Player() {
	texture.free();
}

void Player::handleEvent( SDL_Event& e ){
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
            	mVelY -= DOT_VEL;
            	corrani = UP;
            	break;
            case SDLK_DOWN:
            	mVelY += DOT_VEL;
            	corrani = DOWN;
            	break;
            case SDLK_LEFT:
            	mVelX -= DOT_VEL;
            	corrani = LEFT;
            	break;
            case SDLK_RIGHT:
            	mVelX += DOT_VEL;
            	corrani = RIGHT;
            	break;
            case SDLK_SPACE:
            	if (corrani == RIGHT || corrani == RIGHT1)corrani = RSWORD;
            	if (corrani == LEFT || corrani == LEFT1)corrani = LSWORD;
            	if (corrani == UP || corrani == UP1)corrani = USWORD;
            	if (corrani == DOWN || corrani == DOWN1)corrani = DSWORD;
        }
	}
	//animazione camminata
	if (e.type == SDL_KEYDOWN && e.key.repeat > 0 ){
		unsigned int tick = (SDL_GetTicks())%1000;
		if ((tick > 500 && tick < 750) || (tick < 250) ){
			switch( e.key.keysym.sym )
					{
						case SDLK_UP:
							corrani = UP1;
							break;
						case SDLK_DOWN:
							corrani = DOWN1;
							break;
						case SDLK_LEFT:
							corrani = LEFT1;
							break;
						case SDLK_RIGHT:
							corrani = RIGHT1;
							break;
					}
	}else {
		switch( e.key.keysym.sym )
				{
					case SDLK_UP:
						corrani = UP;
						break;
					case SDLK_DOWN:
						corrani = DOWN;
						break;
					case SDLK_LEFT:
						corrani = LEFT;
						break;
					case SDLK_RIGHT:
						corrani = RIGHT;
						break;
				}
		}
     }

    //If a key was released
    if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:
			mVelY += DOT_VEL;
			corrani = UP;
			break;
		case SDLK_DOWN:
			mVelY -= DOT_VEL;
			corrani = DOWN;
			break;
		case SDLK_LEFT:
			mVelX += DOT_VEL;
			corrani = LEFT;
			break;
		case SDLK_RIGHT:
			mVelX -= DOT_VEL;
			corrani = RIGHT;
			break;
     }
    }

}

int Player::checkCollision( SDL_Rect a, SDL_Rect b ) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	 //If any of the sides from A are outside of B
	if( bottomA <= topB ) { return false; }
	if( topA >= bottomB ) { return false; }
	if( rightA <= leftB ) { return false; }
	if( leftA >= rightB ) { return false; }
	//If none of the sides from A are outside B
	return true;
}

int Player::move(vector<SDL_Rect> Vcollider,vector<Enemy*> *Venemy, vector<Door*> *Vdoor,
		vector<GameObject*> *Vgame, float timeStep ){

	float motx = mVelX * timeStep;
	float moty = mVelY * timeStep;
	//Move the dot left or right
	mPosX = mPosX + motx;
	mCollider.x = static_cast<int>(mPosX);

	//Move the dot up or down
	mPosY = mPosY + moty;
	mCollider.y = static_cast<int>(mPosY);

	// controllo collisioni muri
	bool check = false;
	int size = Vcollider.size();
	for (int i = 0; i < size; i++){
			if (checkCollision(mCollider,Vcollider[i])){
				check = true;
			}
	}

	if (check == true){
		mPosX = mPosX - motx;
		mCollider.x = static_cast<int>(mPosX);
		mPosY = mPosY - moty;
		mCollider.y = static_cast<int>(mPosY);
	}
	//controllo collisione GameObject
	check = false;
		size = Vgame->size();
		bool des = false;
		int ind = -1;
		for (int i = 0; i < size; i++){
				if (checkCollision(mCollider,(*Vgame)[i]->mCollider)){
					if ((*Vgame)[i]->tag == "key" || (*Vgame)[i]->tag == "map" ){
						des = true;
						ind = i;
						if ((*Vgame)[i]->tag == "key") key = true;
						if ((*Vgame)[i]->tag == "map") map = true;
					}
					check = true;
					if ((*Vgame)[i]->tag == "king") {
						checkmate = true;
					}
				}
		}
		if (check == true){
			mPosX = mPosX - motx;
			mCollider.x = static_cast<int>(mPosX);
			mPosY = mPosY - moty;
			mCollider.y = static_cast<int>(mPosY);
		}
		if (des == true){
			(*Vgame).erase((*Vgame).begin() + ind);
		}
	//controllo spada
	if (corrani == LSWORD){
		sword.x = mPosX - 22;
		sword.y = mPosY + P_HEIGHT / 2;
		sword.h = 6;
		sword.w = 22;
	}
	if (corrani == RSWORD){
		sword.x = mPosX + P_WIDTH + 22;
		sword.y = mPosY + P_HEIGHT / 2;
		sword.h = 6;
		sword.w = 22;
	}
	if (corrani == USWORD){
		sword.x = mPosX + P_WIDTH / 2;
		sword.y = mPosY - 22;
		sword.h = 22;
		sword.w = 6;
	}
	if (corrani == DSWORD){
		sword.x = mPosX + P_WIDTH / 2;
		sword.y = mPosY + P_HEIGHT + 22;
		sword.h = 22;
		sword.w = 6;
	}
	//controllo collisioni nemici
	if (inv == false){
		bool checkc = false;
		for (int i = 0; i < (*Venemy).size(); i++){
			if (checkCollision(mCollider,(*Venemy)[i]->mCollider)){
				checkc = true;
		}
		if (checkc == true){
			inv = true;
			texture.setColor(255,0,0);
			checkc = false;
			life = life - 1;
			}
		}
	}else{
		hit = hit + timeStep;
		int temp = int (hit*100) %15;
		if ( temp == 0 || temp == 1 || temp == 2 || temp == 3 || temp == 4 || temp == 5
				|| temp == 6 || temp == 7 ){
			texture.setColor(255,0,0);
		}
		else{
			texture.setColor(255,255,255);
		}
		if (hit > 1.5){
			hit = 0;
			inv = false;
			texture.setColor(255,255,255);
		}
	}
	//controllo animazioni
	if (corrani == LSWORD || corrani == RSWORD || corrani == USWORD || corrani == DSWORD){
		anima = anima + timeStep;
		if (anima > 0.5){
			switch (corrani){
			case LSWORD: corrani = LEFT; break;
			case RSWORD: corrani = RIGHT; break;
			case USWORD: corrani = UP; break;
			case DSWORD: corrani = DOWN; break;
			}
			anima = 0;
		}
	}
	//uccisione nemici
	if (corrani == LSWORD || corrani == RSWORD || corrani == USWORD || corrani == DSWORD){
		int del = -1;
		for (int i = 0; i < (*Venemy).size(); i++){
					if (checkCollision(sword,(*Venemy)[i]->mCollider)){
						del = i;
						break;
				}
		}
		if (del != -1){
			(*Venemy).erase((*Venemy).begin() + del);
			}
	}
	//controllo porte
	for (int i = 0; i < (*Vdoor).size(); i++){
						if (checkCollision(mCollider,(*Vdoor)[i]->mCollider)){
							if (  !((*Vdoor)[i]->lock == true && key == false ) ){
								if ((*Vdoor)[i]->pos == 0) {
									mPosX = SCREEN_WIDTH /2 - P_WIDTH /2;
									mPosY = SCREEN_HEIGHT - WALL_HEIGHT - 38;
								}
								if ((*Vdoor)[i]->pos == 1) {
									mPosX = WALL_HEIGHT + 1;
									mPosY = MENU_HEIGHT + (SCREEN_HEIGHT - MENU_HEIGHT)/2;
								}
								if ((*Vdoor)[i]->pos == 2) {
									mPosX = SCREEN_WIDTH /2 - P_WIDTH /2;
									mPosY = MENU_HEIGHT + WALL_HEIGHT + 1;
								}
								if ((*Vdoor)[i]->pos == 3) {
									mPosX = SCREEN_WIDTH - WALL_HEIGHT - 38;
									mPosY = MENU_HEIGHT + (SCREEN_HEIGHT - MENU_HEIGHT)/2;
								}
								return (*Vdoor)[i]->dest;
							}
					}
	}
	return 0;
}

void Player::render(){
	if (corrani == LSWORD){
		texture.render((int)mPosX - 30,(int)mPosY,48,32,&rect[corrani],gRender);
	}
	else if (corrani == RSWORD){
			texture.render((int)mPosX,(int)mPosY, 48, 32, &rect[corrani],gRender);
		}
	else if (corrani == USWORD){
		texture.render((int)mPosX,(int)mPosY - 32, 30, 54, &rect[corrani],gRender);
	}
	else if (corrani == DSWORD){
			texture.render((int)mPosX,(int)mPosY, 30, 54, &rect[corrani],gRender);
		}
	else texture.render((int)mPosX,(int)mPosY, 30, 32, &rect[corrani],gRender);
}



