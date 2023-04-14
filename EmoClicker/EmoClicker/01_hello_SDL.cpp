/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/
//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "Window.h"
#include "Image.h"
#include "SDL_ImageImageLoader.h"
#include <map>
#include <memory>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


std::map<SDL_KeyCode, const char*> surfaceMap = {
	{SDL_KeyCode::SDLK_UP, "img/up.bmp"},
	{SDL_KeyCode::SDLK_DOWN, "img/down.bmp"},
	{SDL_KeyCode::SDLK_LEFT, "img/left.bmp"},
	{SDL_KeyCode::SDLK_RIGHT, "img/right.bmp"},
};

const char* fallbackSurface{ "img/tearsOfJoy.png" };

int main(int argc, char* args[])
{
	// We decide for now to use the SDL_Image Loader (which only supports BMP):
	IImageLoader* imageLoader = new SDL_ImageImageLoader{};
	// We pass that ImageLoader on to the Window so the Window can use it
	// to load images
	Window window{ SCREEN_WIDTH, SCREEN_HEIGHT, imageLoader };
	//Start up SDL and create window
	if (!window.wasSuccessful())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

	//Load media
	//auto image{ std::make_unique<Image>(fallbackSurface, window.getPixelFormat())};
	auto image{window.loadImage(fallbackSurface)};
	if (!image->wasSuccessful())
	{
		printf("Failed to load media!\n");
		return -1; 
	}



	//while(!window.quit())
	// window.update();

	//Hack to get window to stay up
	SDL_Event e; bool quit = false;

	while (quit == false)
	{
		//loop through all events from Windows (OS)
		while (SDL_PollEvent(&e))
		{
			switch (e.type) {
			case SDL_QUIT: {
				quit = true;
			} break;
			case SDL_KEYDOWN: {
				const char* imgPath = fallbackSurface;
				if (auto result = surfaceMap.find((SDL_KeyCode)e.key.keysym.sym); result != surfaceMap.end()) {
					imgPath = result->second;
				}

				//image = std::make_unique<Image>(imgPath, window.getPixelFormat());
				image = window.loadImage(imgPath);
				if (!image->wasSuccessful())
				{
					printf("Failed to load media!\n");
					return -1;
				}

			} break;
			}
		}
		//when done with all pending events, update the rendered screen
		window.render(image.get());  
	}
	return 0;

}

