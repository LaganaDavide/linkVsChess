/*
 * GameObject.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: laghy
 */

#include "GameObject.h"

GameObject::GameObject() {

}

GameObject::GameObject(SDL_Renderer * r, int posx , int posy, LTexture * tex){
	//Initialize the offsets
	mPosX = posx;
	mPosY = posy;
	//initialize render
	gRender = r;
	//load texture
	texture = tex;
	rect.x = 300;
	rect.y = 128;
	rect.w = 15;
	rect.h = 15;

	mCollider.x = mPosX;
	mCollider.y = mPosY;

	mCollider.h = P_HEIGHT;
	mCollider.w = P_WIDTH;

	tag = "statue";

}

GameObject::GameObject(SDL_Renderer * r, int posx , int posy, LTexture * tex, SDL_Rect clip, string t){
	//Initialize the offsets
	mPosX = posx;
	mPosY = posy;
	//initialize render
	gRender = r;
	//load texture
	texture = tex;
	rect = clip;
	tag = t;

	mCollider.x = mPosX;
	mCollider.y = mPosY;

	mCollider.h = P_HEIGHT;
	mCollider.w = P_WIDTH;


}

GameObject::~GameObject() {

}

void GameObject::render(){
	texture->render(mCollider.x,mCollider.y, mCollider.w ,mCollider.h,&rect,gRender);
}

