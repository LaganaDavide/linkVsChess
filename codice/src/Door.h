/*
 * Door.h
 *
 *  Created on: Mar 25, 2015
 *      Author: laghy
 */

#ifndef DOOR_H_
#define DOOR_H_
#include "LTexture.h"

class Door {
public:
	static const int P_WIDTH = 64;
	static const int P_HEIGHT = 32;
	static const int SCREEN_WIDTH = 512;
	static const int SCREEN_HEIGHT = 448;
	static const int WALL_HEIGHT = 52;
	static const int MENU_HEIGHT = 113;
	Door();
	Door(LTexture* tex, int p, int d,SDL_Renderer* r);
	virtual ~Door();
	int render ();

	//posizione della porta nella stanza 0=alto 1=destra 2=basso 3=sinistra
	int pos;

	//in che stanza si accede tramite la porta
	int dest;

	//se è chiusa
	bool lock;

	//posizione della porta
	SDL_Rect mCollider;

	//texture
	LTexture* texture;

	//clip della texture
	SDL_Rect rect;

	SDL_Renderer* gRender;
};

#endif /* DOOR_H_ */
