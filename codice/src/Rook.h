/*
 * Rook.h
 *
 *  Created on: Apr 2, 2015
 *      Author: laghy
 */

#ifndef ROOK_H_
#define ROOK_H_

#include "Enemy.h"

class Rook: public Enemy {
public:
	static const int MENU_HEIGHT = 113;
	static const int WALL_HEIGHT = 52;
	Rook();
	Rook(SDL_Renderer * r, vector<Enemy*> *ve, int posx , int posy, LTexture * tex);
	virtual ~Rook();
	void move(vector<SDL_Rect> Vcollider, float timeStep );
	void render();

};

#endif /* ROOK_H_ */
