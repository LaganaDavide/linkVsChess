/*
 * GameObject.h
 *
 *  Created on: Mar 31, 2015
 *      Author: laghy
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "LTexture.h"

class GameObject {
public:
	static const int P_WIDTH = 34;
	static const int P_HEIGHT = 33;
	static const int SCREEN_WIDTH = 512;
	static const int SCREEN_HEIGHT = 448;

	GameObject();
	GameObject(SDL_Renderer * r, int posx , int posy, LTexture * tex);
	GameObject(SDL_Renderer * r, int posx , int posy, LTexture * tex, SDL_Rect clip, string t);
	virtual ~GameObject();
	virtual void render();

	float mPosX, mPosY;
	LTexture *texture;
	SDL_Renderer* gRender;
	SDL_Rect rect;
	//collision box
	SDL_Rect mCollider;
	//tag
	string tag;
};

#endif /* GAMEOBJECT_H_ */
