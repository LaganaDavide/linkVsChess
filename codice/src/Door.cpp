/*
 * Door.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: laghy
 */

#include "Door.h"

Door::Door(){
	texture = NULL;
	pos = 0;
	dest = 0;
	gRender = NULL;
}

Door::~Door(){

}

Door::Door(LTexture* tex, int p, int d, SDL_Renderer * r){
	texture = tex;
	pos = p;
	dest = d;
	lock = false;
	mCollider.h= P_HEIGHT;
	mCollider.w = P_WIDTH;
	if (pos == 0){
		mCollider.x = SCREEN_WIDTH/2 - P_WIDTH/2;
		mCollider.y = MENU_HEIGHT + WALL_HEIGHT - P_HEIGHT + 2 ;

	}
	if (pos == 1){
			mCollider.x = SCREEN_WIDTH - WALL_HEIGHT -1 ;
			mCollider.y = (SCREEN_HEIGHT - MENU_HEIGHT )/2  + MENU_HEIGHT - P_HEIGHT/2 ;
			mCollider.w = P_HEIGHT;
			mCollider.h = P_WIDTH;
		}
	if (pos == 2){
			mCollider.x = SCREEN_WIDTH/2 - P_WIDTH/2 ;
			mCollider.y = SCREEN_HEIGHT - WALL_HEIGHT - 2;
		}
	if (pos == 3){
			mCollider.x = WALL_HEIGHT - P_HEIGHT + 1 ;
			mCollider.y = (SCREEN_HEIGHT - MENU_HEIGHT )/2  + MENU_HEIGHT - P_HEIGHT/2 ;
			mCollider.w = P_HEIGHT;
			mCollider.h = P_WIDTH;
		}

	rect.x = 242;
	rect.y = 48;
	rect.w = 33;
	rect.h = 21;

	gRender = r;
}

int Door::render(){
	if (pos == 0){
	texture->render(mCollider.x,mCollider.y,mCollider.w,mCollider.h,&rect,gRender);
	}
	if (pos ==1 ){
		double a = 90;
		texture->render(mCollider.x -19 ,mCollider.y,P_WIDTH,P_HEIGHT,&rect,a,NULL,gRender);
	}
	if (pos ==2 ){
		double a = 180;
		texture->render(mCollider.x,mCollider.y,mCollider.w,mCollider.h,&rect,a,NULL,gRender);
	}
	if (pos == 3){
		double a = -90;
		texture->render(mCollider.x - 15,mCollider.y,P_WIDTH,P_HEIGHT,&rect,a,NULL,gRender);
	}
	return 0;
}
