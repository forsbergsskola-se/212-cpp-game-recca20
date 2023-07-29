#include "MapScreen.h"

MapScreen::MapScreen(SDL_Renderer* renderer, Hero* hero, int* items) 
{
	this->renderer = renderer;
	this->hero = hero;
	this->items = items;

	//loop through map using nested loop and clear all values out to be zero(walls)
	for (int x = 0; x <= 9; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			map[x][y] = 0;
		}
	}
}

MapScreen::~MapScreen()
{

}

void MapScreen::draw()
{
	//MAP DRAWING
	//tile representing size of 1 grid thing from map
	SDL_Rect tileRect = { 0,0,32,32 };
	//loop through and draw each grid value from map array
	for (int x = 0; x <= 9; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			//IF is ground, set draw colour to ground colour
			//ELSE set to wall colour
			if (map[x][y] == 1)
			{
				SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
			}
			else 
			{
				//walls
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			//MOVE rectangle to grid position with regards to tile width/height
			tileRect.x = x * tileRect.w;
			tileRect.y = y * tileRect.h;
			//draw rectangle to screen using current draw colourl
			SDL_RenderFillRect(renderer, &tileRect);
		}
	}
}