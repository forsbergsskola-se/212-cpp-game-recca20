#include "Image.h"
#include <SDL_image.h>
#include "SDL.h"								
#include <cstdio>

Image::Image(SDL_Surface* surface) :
	imageSurface{surface},
	success{surface != nullptr},
	x{},
	y{},
	width{ 100 },
	height{ 100 } {}

Image::~Image() {
	//Deallocate surface
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;


}

