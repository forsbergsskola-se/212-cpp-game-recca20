#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Hero.h"
#include "MapObject.h"
#include <list> // is a container that can shrink and grow (others vector, map, queue, stack)

#include <fstream>//file stream

using namespace std;

class MapScreen
{
public:
	Hero* hero;//reference hero to built inside main.cpp
	int* items;//going to use this to reference items[10] from main.cpp

	SDL_Renderer* renderer;

	//2d array representing the map. 0 values = walls, 1 values = can walk/ground
	int map[10][10];
	MapObject heroObj;
	MapObject door;
	list<MapObject> mapObjects;

	MapScreen(SDL_Renderer* renderer, Hero* hero, int* items);
	~MapScreen();

	void draw();
};

