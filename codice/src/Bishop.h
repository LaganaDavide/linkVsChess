/*
 * Bishop.h
 *
 *  Created on: Mar 26, 2015
 *      Author: laghy
 */

#ifndef BISHOP_H_
#define BISHOP_H_

#include "Enemy.h"
#include "LTexture.h"

class Bishop: public Enemy {
public:
	static const int MENU_HEIGHT = 113;
	static const int WALL_HEIGHT = 52;
	Bishop();
	Bishop(SDL_Renderer * r, vector<Enemy*> *ve, int posx , int posy, LTexture * tex);
	virtual ~Bishop();
	void move(vector<SDL_Rect> Vcollider, float timeStep );
	void render();

};

#endif /* BISHOP_H_ */
