/*
 * Queen.h
 *
 *  Created on: Apr 2, 2015
 *      Author: laghy
 */

#ifndef QUEEN_H_
#define QUEEN_H_

#include "Enemy.h"

class Queen: public Enemy {
public:
	static const int MENU_HEIGHT = 113;
	static const int WALL_HEIGHT = 52;
	Queen();
	Queen(SDL_Renderer * r, vector<Enemy*> *ve, int posx , int posy, LTexture * tex);
	virtual ~Queen();
	void move(vector<SDL_Rect> Vcollider, float timeStep );
	void render();
};

#endif /* QUEEN_H_ */
