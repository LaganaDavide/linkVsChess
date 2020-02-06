/*
 * LTexture.h
 *
 *  Created on: Jan 27, 2015
 *      Author: laghy
 */

#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

class LTexture {
public:
	LTexture();
	virtual ~LTexture();

	//Loads image at specified path bool
	bool loadFromFile( std::string path , SDL_Renderer* Renderer );
	//Deallocates texture
	void free();
	//Renders texture at given point
	void render( int x, int y, SDL_Rect* clip , SDL_Renderer *Renderer);
	void render( int x, int y, int w, int h, SDL_Rect* clip, SDL_Renderer *Renderer);
	void render( int x, int y,int w , int h, SDL_Rect* clip, double angle, SDL_Point* center,
			SDL_Renderer *Renderer ,SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );
	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif /* LTEXTURE_H_ */
