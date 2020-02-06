/*

 * LoadLevel.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: laghy
 */

#include "LoadLevel.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <vector>


bool LoadLevel::Load(int lev, LTexture* BackgroundTexture,LTexture* Etexture, LTexture* Ptexture, Player* player, vector<Enemy*> *Ve ,
		vector<SDL_Rect>* Vcol, vector<Door*> *vd, vector<GameObject*> *vg, SDL_Renderer* gRenderer ){
	bool success = true;

	if (!BackgroundTexture->loadFromFile("src/sprite/Tiles_Sets.png",gRenderer)){
			success = false;
			printf ("non carico la texture\n");
		}
	//cancello ogetti precedenti
	Vcol->clear();
	for (int i=0; i<vd->size(); i++) {
		delete (*vd)[i];
	}
	vd->clear();
	for (int i=0; i< Ve->size(); i++) {
		delete (*Ve)[i];
	}
	Ve->clear();
	for (int i=0; i<vg->size(); i++) {
		delete (*vg)[i];
	}
	vg->clear();

	//collider vector inizialize
	(*Vcol).resize(4);


	//inizializzo i muri
	//muro in basso
	(*Vcol)[0].x = 0;
	(*Vcol)[0].y = SCREEN_HEIGHT - WALL_HEIGHT;
	(*Vcol)[0].w = SCREEN_WIDTH;
	(*Vcol)[0].h = WALL_HEIGHT;
	//muro in alto
	(*Vcol)[1].x = 0;
	(*Vcol)[1].y = MENU_HEIGHT;
	(*Vcol)[1].w = SCREEN_WIDTH;
	(*Vcol)[1].h = WALL_HEIGHT;
	//muro a destra
	(*Vcol)[2].x = SCREEN_WIDTH - WALL_HEIGHT;
	(*Vcol)[2].y = 0;
	(*Vcol)[2].w = WALL_HEIGHT;
	(*Vcol)[2].h = SCREEN_HEIGHT;
	//muro a sinistra
	(*Vcol)[3].x = 0;
	(*Vcol)[3].y = 0;
	(*Vcol)[3].w = WALL_HEIGHT;
	(*Vcol)[3].h = SCREEN_HEIGHT;

	//Open the map
	 	stringstream ss;
	    ss << lev;
		string path = "src/level/level" + ss.str();
		char * writable = new char[path.size() + 1];
		std::copy(path.begin(), path.end(), writable);
		writable[path.size()] = '\0';

		std::ifstream map( writable );
		if( map == NULL )
		{
			printf( "Unable to load map file!\n" );
		}
		delete[] writable;
		//door
		int door = -1;
		int des = -1;
		int l = -1;
		for( int i = 0; i < 4; ++i ){
			map >> door;
			map >> des;
			map >> l;
			if (door == 1){
				Door* nd = new Door(BackgroundTexture,i,des,gRenderer);
				if (l == 1){
					nd->lock = true;
					nd->rect.x = 243;
					nd->rect.y = 86;
				}
				vd->push_back(nd);

			}
		}
		//The tile offsets
		int x = WALL_HEIGHT;
		int y = MENU_HEIGHT + WALL_HEIGHT ;
		//If the map couldn't be loaded

		for( int i = 0; i < TOTAL_TILES; ++i ){
			int tileType = -1;
			map >> tileType;
			if( map.fail() )
			{
				printf( "Error loading map: Unexpected end of file!\n" );
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < 11 ) ){
				GameObject* nuovo = NULL;
				SDL_Rect cl = {0,0,0,0};
				switch (tileType){
				case 0: break;
				case 1:
					Ve->push_back( new Enemy(gRenderer,Ve, x , y, Etexture ));
					break;
				case 2:
					Ve->push_back( new Bishop(gRenderer,Ve, x , y, Etexture ));
					break;
				case 3:
					Ve->push_back( new Rook(gRenderer,Ve, x , y, Etexture ));
					break;
				case 4:
					Ve->push_back( new Queen(gRenderer,Ve, x , y, Etexture ));
					break;
				case 5:
					vg->push_back(new GameObject(gRenderer,x,y,BackgroundTexture));
					break;
				case 6:
					nuovo = new GameObject(gRenderer,x,y,BackgroundTexture);
					nuovo->rect.x = 280;
					nuovo->rect.y = 129;
					vg->push_back(nuovo);
					break;
				case 7:
					nuovo = new GameObject(gRenderer,x,y,BackgroundTexture);
					nuovo->rect.x = 242;
					nuovo->rect.y = 129;
					vg->push_back(nuovo);
					break;
				case 8:
					cl = {23,2,17,17};
					nuovo = new GameObject(gRenderer,x,y ,Etexture,cl, "king");
					nuovo->mCollider.h = 40;
					nuovo->mCollider.w = 40;
					vg->push_back(nuovo);
					break;
				case 9:
					cl = {362,254,10,17};
					vg->push_back(new GameObject(gRenderer, WALL_HEIGHT + 40, MENU_HEIGHT + WALL_HEIGHT + 40 , Ptexture ,cl, "key"));
					break;
				case 10:
					cl = {274,255,10,17};
					vg->push_back(new GameObject(gRenderer, SCREEN_WIDTH - WALL_HEIGHT - 40, MENU_HEIGHT + WALL_HEIGHT + 40 , Ptexture ,cl, "map"));
					break;
				}
			}
			//If we don't recognize the tile type
			else{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				break;
			}
			x += TILE_WIDTH;
			//If we've gone too far
			if( x >= SCREEN_WIDTH - WALL_HEIGHT ){
				x = WALL_HEIGHT;
				y += TILE_HEIGHT;
			}
		}

}
