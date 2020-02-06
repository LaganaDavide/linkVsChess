/*
 * Rook.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: laghy
 */

#include "Rook.h"

Rook::Rook() {
	// TODO Auto-generated constructor stub

}

Rook::Rook(SDL_Renderer * r, vector<Enemy*> *ve, int posx , int posy, LTexture * tex){
	//Initialize the offsets
	mPosX = posx;
	mPosY = posy;
	//Initialize the velocity
	mVelX = 0;
	mVelY = DOT_VEL *3;
	//initialize step
	step = 0;
	//initialize render
	gRender = r;
	//load texture
	texture = tex;
	rect.x = 46;
	rect.y = 3;
	rect.w = 13;
	rect.h = 16;

	mCollider.x = mPosX;
	mCollider.y = mPosY;

	mCollider.h = P_HEIGHT + 4;
	mCollider.w = P_WIDTH + 5;
}

Rook::~Rook() {
	// TODO Auto-generated destructor stub
}

void Rook::move(vector<SDL_Rect> Vcollider, float timeStep ){
	float motx = mVelX * timeStep;
	float moty = mVelY * timeStep;
	//Move the dot left or right
	mPosX = mPosX + motx;
	mCollider.x = mPosX;
	//Move the dot up or down
	mPosY = mPosY + moty;
	step = step + timeStep;
	mCollider.y = mPosY;
	int check = 0;
	int size = Vcollider.size();
	for (int i = 0; i < size; i++){
		int t =checkCollision(mCollider,Vcollider[i]);
			if (t == true){
				check = t;
				break;
			}
	}
	if (check == true){
		if (mPosX >= SCREEN_WIDTH - WALL_HEIGHT - P_WIDTH -5 || mPosX <= WALL_HEIGHT)mVelX = - mVelX;
		if (mPosY >= SCREEN_HEIGHT - WALL_HEIGHT - P_WIDTH  -5 || mPosY <= MENU_HEIGHT + WALL_HEIGHT)mVelY = -mVelY;
		mPosX = mPosX - motx;
		mCollider.x = static_cast<int>(mPosX);
		mPosY = mPosY - moty;
		mCollider.y = static_cast<int>(mPosY);
	}
}

void Rook::render(){
	texture->render((int)mPosX,(int)mPosY,mCollider.h,mCollider.w ,&rect,gRender);
}
