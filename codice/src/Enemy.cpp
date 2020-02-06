/*
 * Enemy.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: laghy
 */

#include "Enemy.h"

Enemy::Enemy() {
	mPosX = SCREEN_WIDTH / 2 ;
	mPosY = SCREEN_HEIGHT / 2 ;
	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
	step = 0;
	//initialize render
	gRender = NULL;
	texture = NULL;
	mCollider.x = 0;
	mCollider.y = 0;
	mCollider.h = 0;
	mCollider.w = 0;
}

Enemy::~Enemy() {
}

Enemy::Enemy(SDL_Renderer * r, vector<Enemy*> *ve, int posx , int posy, LTexture * tex){
	//Initialize the offsets
	mPosX = posx;
	mPosY = posy;
	//Initialize the velocity
	mVelX = DOT_VEL;
	mVelY = 0;
	//initialize step
	step = 0;
	//initialize render
	gRender = r;
	//load texture
	texture = tex;
	rect.x = 68;
	rect.y = 4;
	rect.w = 11;
	rect.h = 15;

	mCollider.x = mPosX;
	mCollider.y = mPosY;

	mCollider.h = P_HEIGHT;
	mCollider.w = P_WIDTH;
}

void Enemy::move(vector<SDL_Rect> Vcollider, float timeStep ){
	float motx = mVelX * timeStep;
	float moty = mVelY * timeStep;
	//Move the dot left or right
	mPosX = mPosX + motx;
	mCollider.x = mPosX;
	//Move the dot up or down
	mPosY = mPosY + moty;
	step = step + timeStep;
	mCollider.y = mPosY;
	bool check = false;
			int size = Vcollider.size();
			for (int i = 0; i < size; i++){
					if (checkCollision(mCollider,Vcollider[i])){
						check = true;
					}
			}
	if (step > 2){
		int ran = rand()%4;
		if (ran == 0){
			mVelX = DOT_VEL;
			mVelY = 0;
			step = 0;
		}
		if (ran == 1){
			mVelX = 0;
			mVelY = DOT_VEL;
			step = 0;
			}
		if (ran == 2 ){
			mVelX = 0;
			mVelY = -DOT_VEL;
			step = 0;
		}
		if (ran == 3){
			mVelX = -DOT_VEL;
			mVelY = 0;
			step = 0;
			}
		}
	if (check == true){
		mPosX = mPosX - motx;
		mCollider.x = static_cast<int>(mPosX);
		mPosY = mPosY - moty;
		mCollider.y = static_cast<int>(mPosY);
		}
	}

void Enemy::render(){
	texture->render((int)mPosX,(int)mPosY,P_HEIGHT,P_WIDTH,&rect,gRender);
}

int Enemy::checkCollision( SDL_Rect a, SDL_Rect b ) {
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
