/*
 * World.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: laghy
 */

#include "World.h"

World::World() {
	state = FISTSCREEN;
	room = 0;
	gRenderer = NULL;
	rectBack.h = 480;
	rectBack.w = 640;
	rectBack.x = 0;
	rectBack.y = 0;
}

World::World(SDL_Renderer * ren){
	state = FISTSCREEN;
	gRenderer = ren;
	room = 0;
	player = NULL;
	if (!BackgroundTexture.loadFromFile("src/sprite/fist.png",gRenderer)){
			printf ("non carico la texture\n");
		}
	rectBack.h = 480;
	rectBack.w = 640;
	rectBack.x = 0;
	rectBack.y = 0;
}

World::~World() {
	BackgroundTexture.~LTexture();
	player->~Player();
}

bool World::HandleEvent(SDL_Event& e){

	switch (state){
	case(FISTSCREEN):
			if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_RETURN){
					state = UNINIT;
					room = 0;
				}
			}
			break;
	case(PLAYING):
		player->handleEvent(e);
		break;
	case(GAMEOVER):
		if (e.type == SDL_KEYDOWN){
						//il giocatore ricomincia la partita
						if (e.key.keysym.sym == SDLK_RETURN){
							//cancello tutto
							player->~Player();
							delete player;
							for (int i=0; i<Vdoor.size(); i++) {
								delete Vdoor[i];
							}
							Vdoor.clear();
							for (int i=0; i<Venemy.size(); i++) {
								delete Venemy[i];
							}
							Venemy.clear();
							for (int i=0; i<Vgame.size(); i++) {
								delete Vgame[i];
							}
							Vgame.clear();
							//reinizializzo
							state = FISTSCREEN;
							room = 0;
							player = NULL;
							if (!BackgroundTexture.loadFromFile("src/sprite/fist.png",gRenderer)){
									printf ("non carico la texture\n");
								}
						}
						//chiudo il gioco
						if (e.key.keysym.sym == SDLK_q){
							//cancello tutto
							player->~Player();
							delete player;
							for (int i=0; i<Vdoor.size(); i++) {
								delete Vdoor[i];
							}
							Vdoor.clear();
							for (int i=0; i<Venemy.size(); i++) {
								delete Venemy[i];
							}
							Venemy.clear();
							for (int i=0; i<Vgame.size(); i++) {
								delete Vgame[i];
							}
							Vgame.clear();
							return false;
						}
					}
	}
	return true;
}

bool World::UpdateWorld(float timeStep){
	int nr = 0;
	switch (state){
	case(FISTSCREEN):
			return true;
			break;
	case(UNINIT):
			if (!Ptexture.loadFromFile( "src/sprite/link_sheet.png" ,gRenderer) ){
				printf( "Failed to load sprite texture image!\n" );
			}
			if (!Etexture.loadFromFile( "src/sprite/chess.png" ,gRenderer) ){
					printf( "Failed to load sprite texture image!\n" );
				}
			player = new Player(gRenderer,&Ptexture,SCREEN_WIDTH/2 -16 ,SCREEN_HEIGHT - WALL_HEIGHT - 70);
			rectBack.x = 0;
			rectBack.y = 12;
			rectBack.w = 240;
			rectBack.h = 160;
			LoadLevel::Load(1,&BackgroundTexture,&Etexture,&Ptexture,player,&Venemy,&Vwall,&Vdoor,&Vgame,gRenderer);
			state = PLAYING;
			break;
	case(PLAYING):
			nr = player->move(Vwall,&Venemy,&Vdoor,&Vgame,timeStep);
			for (int i = 0; i < Venemy.size(); i++){
					Venemy[i]->move(Vwall,timeStep);
				}
			if (player->life <=  0){
				state = GAMEOVER;
				rectBack.h = 480;
				rectBack.w = 640;
				rectBack.x = 0;
				rectBack.y = 0;
				if (!BackgroundTexture.loadFromFile( "src/sprite/Game_Over.png" ,gRenderer) ){
								printf( "Failed to load sprite texture image!\n" );
						}
			}
			if (player->checkmate == true){
							state = GAMEOVER;
							rectBack.h = 480;
							rectBack.w = 640;
							rectBack.x = 0;
							rectBack.y = 0;
							if (!BackgroundTexture.loadFromFile( "src/sprite/win.jpg" ,gRenderer) ){
											printf( "Failed to load sprite texture image!\n" );
										}
			}
			if (nr != 0){
				LoadLevel::Load(nr,&BackgroundTexture,&Etexture,&Ptexture, player,&Venemy,&Vwall,&Vdoor,&Vgame,gRenderer);
				room = 0;
			}
			break;
	case(GAMEOVER):
		break;
	}
	return true;
}


bool World::RenderWorld(){
	switch (state)
	{
		case(FISTSCREEN):
			BackgroundTexture.render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, &rectBack,gRenderer);
			break;
		case(PLAYING):
			BackgroundTexture.render(0,MENU_HEIGHT,SCREEN_WIDTH, 335, &rectBack,gRenderer);
			SDL_Rect cuore;
			cuore.h = 9;
			cuore.w = 9;
			cuore.x = 243;
			cuore.y = 198;
			SDL_Rect cl;
			cl.x = 362;
			cl.y = 254;
			cl.h = 17;
			cl.w = 10;
			for (int j = 0 ; j < player->life; j++){
				Ptexture.render(SCREEN_WIDTH/2 + 20 + (j*20),50,20,20,&cuore,gRenderer);
			}
			if (player-> key == true){
				Ptexture.render(SCREEN_WIDTH/2 + 20,80,20,20,&cl,gRenderer);
			}
			for (int i = 0; i < Vdoor.size(); i++){
							Vdoor[i]->render();
						}
			for (int i = 0; i < Venemy.size(); i++){
				Venemy[i]->render();
			}
			for (int i = 0; i < Vgame.size(); i++){
							Vgame[i]->render();
						}
			if (player->map == true){
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
				SDL_Rect outlineRect = { SCREEN_HEIGHT / 6, 20, 20, 10 };
				SDL_RenderDrawRect( gRenderer, &outlineRect );
				if (room == 4) SDL_RenderFillRect( gRenderer, &outlineRect );

				outlineRect = { SCREEN_HEIGHT / 6, 30, 20, 10 };
				SDL_RenderDrawRect( gRenderer, &outlineRect );
				if (room == 1) SDL_RenderFillRect( gRenderer, &outlineRect );

				outlineRect = { SCREEN_HEIGHT / 6, 40, 20, 10 };
				SDL_RenderDrawRect( gRenderer, &outlineRect );
				if (room == 0) SDL_RenderFillRect( gRenderer, &outlineRect );

				outlineRect = { SCREEN_HEIGHT / 6 - 20, 30, 20, 10 };
				SDL_RenderDrawRect( gRenderer, &outlineRect );
				if (room == 3) SDL_RenderFillRect( gRenderer, &outlineRect );

				outlineRect = { SCREEN_HEIGHT / 6 + 20, 30, 20, 10 };
				SDL_RenderDrawRect( gRenderer, &outlineRect );
				if (room == 2) SDL_RenderFillRect( gRenderer, &outlineRect );
			}
			player->render();
			break;
		case(GAMEOVER):
			BackgroundTexture.render(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, &rectBack,gRenderer);
			break;
	}
	return true;
}


