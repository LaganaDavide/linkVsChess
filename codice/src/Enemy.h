/*
 * Enemy.h
 *
 *  Created on: Mar 10, 2015
 *      Author: laghy
 */

#ifndef ENEMY_H_
#define ENEMY_H_
#include "LTexture.h"
#include "LTimer.h"
#include "stdlib.h"
#include <vector>

class Enemy {
public:
	static const int P_WIDTH = 32;
	static const int P_HEIGHT = 32;
	static const int SCREEN_WIDTH = 512;
	static const int SCREEN_HEIGHT = 448;
	 //Maximum axis velocity of the player
	static const int DOT_VEL = 30;

	Enemy();
	Enemy(SDL_Renderer * r, vector<Enemy*> *ve, int posx , int posy, LTexture * tex);
	virtual ~Enemy();
	virtual void move(vector<SDL_Rect> Vcollider, float timeStep);
	virtual void render();
	virtual int checkCollision( SDL_Rect a, SDL_Rect b );

	float mPosX, mPosY;
	float mVelX, mVelY;
	//per decidere quando fare cambiare direzione al nemico
	float step;
	LTexture *texture;
	SDL_Renderer* gRender;
	SDL_Rect rect;
	//collision box
	SDL_Rect mCollider;
};

#endif /* ENEMY_H_ */
