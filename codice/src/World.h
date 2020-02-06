/*
 * World.h
 *
 *  Created on: Mar 17, 2015
 *      Author: laghy
 */

#ifndef WORLD_H_
#define WORLD_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "LTimer.h"
#include "Enemy.h"
#include "Player.h"
#include "LoadLevel.h"
#include "Door.h"
#include "GameObject.h"
using namespace std;


class World {
public:
	//Screen dimension constants
	static const int SCREEN_WIDTH = 512;
	static const int SCREEN_HEIGHT = 448;
	static const int WALL_HEIGHT = 52;
	static const int MENU_HEIGHT = 113;
	World();
	World(SDL_Renderer* ren);
	virtual ~World();
	bool UpdateWorld(float timeStep);
	bool RenderWorld();
	bool HandleEvent(SDL_Event& e);

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//background
	LTexture BackgroundTexture;

	//texture player
	LTexture Ptexture;

	//texture enemy
	LTexture Etexture;

	//rect for background
	SDL_Rect rectBack;

	//Player
	Player * player = NULL;

	//enemyVector
	vector<Enemy*> Venemy;

	//rect for wall
	vector<SDL_Rect> Vwall;

	//rect for door
	vector<Door*> Vdoor;

	//rect for GameOBject
	vector<GameObject*> Vgame;

	//game state
	enum gameState {UNINIT,GAMEOVER, PAUSE, FISTSCREEN, PLAYING};

	gameState state;
	//numero della stanza in cui mi trovo
	int room;

};

#endif /* WORLD_H_ */
