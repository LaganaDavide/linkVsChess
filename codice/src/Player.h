/*
 * Player.h
 *
 *  Created on: Jan 27, 2015
 *      Author: laghy
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "LTexture.h"
#include "LTimer.h"
#include <vector>
#include "Enemy.h"
#include "Door.h"
#include "GameObject.h"
using namespace std;
class Player {

public:
	static const int P_WIDTH = 32;
	static const int P_HEIGHT = 32;
	static const int WALL_HEIGHT = 52;
	static const int MENU_HEIGHT = 113;
	static const int SCREEN_WIDTH = 512;
	static const int SCREEN_HEIGHT = 448;
	 //Maximum axis velocity of the player
	static const int DOT_VEL = 160;
	enum animation {UP,UP1,DOWN,DOWN1,RIGHT,RIGHT1,LEFT,LEFT1, RSWORD, LSWORD, USWORD, DSWORD, WALKING_ANIMATION_FRAMES};
	Player();
	Player ( SDL_Renderer * r , LTexture* Pt, int posx, int posy);
	virtual ~Player();
	//Takes key presses and adjusts the dot's velocity
	void handleEvent( SDL_Event& e );
	//Moves the dot
	int move(vector<SDL_Rect> Vcollider,vector<Enemy*> *Venemy, vector<Door*> *Vdoor, vector<GameObject*> *vg, float timeStep );
	//Shows the dot on the screen
	void render();
	//Box collision detector
	int checkCollision( SDL_Rect a, SDL_Rect b );
	//The X and Y offsets of the player
	float mPosX, mPosY;
	//vita del giocatore
	int life;
	//se il giocatore ha la chiave
	bool key;
	//se il giocatore ha la mappa
	bool map;
	//il giocatore a colpito il re
	bool checkmate;
	//collision box
	SDL_Rect mCollider;
private:
	//The velocity of the player
	float mVelX, mVelY;
	//texture
	LTexture texture;
	//renderer
	SDL_Renderer* gRender;
	//rect for sprite
	SDL_Rect rect[ WALKING_ANIMATION_FRAMES ];
	//posizione spada
	SDL_Rect sword;
	//corrent animation
	int corrani;
	//conta il tempo per l'animazione dell'attacco
	float anima;
	//conta il tempo per il secondo di invicibilità dopo che si viene colpiti
	float hit;
	//mi dice se posso essere colpito o no
	bool inv;
};

#endif /* PLAYER_H_ */
