/*
 * LoadLevel.h
 *
 *  Created on: Mar 18, 2015
 *      Author: laghy
 */

#ifndef LOADLEVEL_H_
#define LOADLEVEL_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include "LTexture.h"
#include "Player.h"
#include "Enemy.h"
#include "Door.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "GameObject.h"

class LoadLevel {
public:
	//Screen dimension constants
	static const int SCREEN_WIDTH = 512;
	static const int SCREEN_HEIGHT = 448;
	static const int WALL_HEIGHT = 52;
	static const int MENU_HEIGHT = 113;
	static const int P_WIDTH = 32;
	static const int TOTAL_TILES = 7 * 12;
	static const float TILE_WIDTH = 34;
	static const int TILE_HEIGHT = 33;

	static bool Load(int lev, LTexture* BackgroundTexture,LTexture* Etexture, LTexture* Ptexture, Player* player, vector<Enemy*> *Ve ,
				vector<SDL_Rect>* Vcol, vector<Door*> *vd, vector<GameObject*> *vg, SDL_Renderer* gRenderer );

	static bool LoadR0(LTexture* BackgroundTexture,LTexture* Etexture, LTexture* Ptexture, Player* player, vector<Enemy*> *Ve ,
			vector<SDL_Rect>* Vcol, vector<Door*> *vd, vector<GameObject*> *vg, SDL_Renderer* gRenderer );
	static bool LoadR1(LTexture* BackgroundTexture,LTexture* Etexture, LTexture* Ptexture, Player* player, vector<Enemy*> *Ve ,
			vector<SDL_Rect>* Vcol, vector<Door*> *vd, vector<GameObject*> *vg, SDL_Renderer* gRenderer );
	static bool LoadR2(LTexture* BackgroundTexture,LTexture* Etexture, LTexture* Ptexture, Player* player, vector<Enemy*> *Ve ,
			vector<SDL_Rect>* Vcol, vector<Door*> *vd, vector<GameObject*> *vg, SDL_Renderer* gRenderer );
	static bool LoadR3(LTexture* BackgroundTexture,LTexture* Etexture, LTexture* Ptexture, Player* player, vector<Enemy*> *Ve ,
			vector<SDL_Rect>* Vcol, vector<Door*> *vd, vector<GameObject*> *vg, SDL_Renderer* gRenderer );
	static bool LoadR4(LTexture* BackgroundTexture,LTexture* Etexture, LTexture* Ptexture, Player* player, vector<Enemy*> *Ve ,
			vector<SDL_Rect>* Vcol, vector<Door*> *vd, vector<GameObject*> *vg, SDL_Renderer* gRenderer );
};

#endif /* LOADLEVEL_H_ */
