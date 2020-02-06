//============================================================================
// Name        : linkVsChess.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "LTimer.h"
#include <stdio.h>
#include <string>
#include "World.h"

//Screen dimension constants
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 448;



//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//world of the game
World* world;

bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Link vs Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main() {
	if( !init() ){
				printf( "Failed to initialize!\n" );
			}else{
				world = new World(gRenderer);
				//Main loop flag
				bool quit = false;
				//Event handler
				SDL_Event e;
				//Keeps track of time between steps
				LTimer stepTimer;
				//While application is running
				while( !quit ) {
					//Handle events on queue
					while( SDL_PollEvent( &e ) != 0 ) {
						//User requests quit
						if( e.type == SDL_QUIT ) {
							quit = true;
						}
						//world handle event
						if(!world->HandleEvent(e)){
							quit = true;
						}
					}
					//Calculate time step (tempo dall'ultimo aggiornamento)
					float timeStep = stepTimer.getTicks() / 1000.f;
					//Restart step timer
					stepTimer.start();
					//world update
					world->UpdateWorld(timeStep);
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0);
					SDL_RenderClear( gRenderer );
					//world draw
					world->RenderWorld();
					//Update screen
					SDL_RenderPresent( gRenderer );

			}
			world->~World();
			close();
		}
}
