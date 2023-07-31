#include "MapScreen.h"

MapScreen::MapScreen(SDL_Renderer* renderer, Hero* hero, int* items) 
{
	//NOTE:computer code random is pseudorandom (fake random)
	//setting a seed value for the random algorithm will generate a set of numbers which appear random
	//if we use thesame seed value each time then we'll get the exact same 'random' outcomes
	//THEREFORE we will set the seed as a changing value, the seconds since start of the year 
	//so that the seed value is different each time we run the game
	srand(time(NULL));

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
	//manual room building
	map[1][1] = 1;
	map[2][1] = 1;
	map[3][1] = 1;
	/*map[1][2] = 1;
	map[2][2] = 1;
	map[3][2] = 1;*/

	//Open map text file
	fstream mapFile("assets/map.txt");
	if (mapFile.is_open())
	{
		for (int y = 0; y <= 9; y++)
		{
			for (int x = 0; x <= 9; x++)
			{
				//read in a single character from where we are up to in the file
				char grid;
				mapFile >> grid;
				if (grid == '0')
				{
					map[x][y] = 0; //wall
				}
				else
				{
					map[x][y] = 1;//land

					//TODO was it a hero, glob, chest or mimic???
					if (grid == 'h')
					{
						heroObj.type = 1;
						heroObj.x = x;
						heroObj.y = y;
					}
					else if (grid == 'd')
					{
						door.type = 2;
						door.x = x;
						door.y = y;
					}
					else if (grid == 'c')
					{
						MapObject chest;
						chest.type = 5;
						chest.x = x;
						chest.y = y;

						mapObjects.push_back(chest);
					}
					else if (grid == 'g')
					{
						MapObject glob;
						glob.type = 3;
						glob.x = x;
						glob.y = y;

						mapObjects.push_back(glob);
					}
					else if (grid == 'm')
					{
						MapObject mimic;
						mimic.type = 4;
						mimic.x = x;
						mimic.y = y;

						mapObjects.push_back(mimic);
					}
				}
			}
		}
	}
	//close file
	mapFile.close();

	//LOAD UP TILE TEXTURES
	heroTexture = IMG_LoadTexture(renderer, "assets/girlTile.png");
	doorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
	globTexture = IMG_LoadTexture(renderer, "assets/globTile.png");
	chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");

	//setup info box
	infoBox.setup(renderer);
	infoBox.setText("Welcome to the Dungeon!");

}

MapScreen::~MapScreen()
{
	//CLEANUP TEXTURE MEMORY
	SDL_DestroyTexture(heroTexture);
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyTexture(globTexture);
	SDL_DestroyTexture(chestTexture);
}

void MapScreen::itemFound()
{
	//randomly pick an item (between 1-4)
	int item = rand() % 4 + 1;//rand gets next number out of random number set (value between 0-2147483647)
	//try find a free slot for this item!
	bool freeSlotFount = false;
	for (int i = 0; i < 10; i++)
	{
		//once find free slot, set it to the item and exit the loop
		if (items[i] == 0)
		{
			freeSlotFount = true;
			items[i] = item;
			break;//exits the loop
		}
	}

	if (freeSlotFount)
	{
		if (item == 1)
			infoBox.setText("Found chocolate!");
		if (item == 2)
			infoBox.setText("Found grenade!");
		if (item == 3)
			infoBox.setText("Found ATK Boost!");
		if (item == 4)
			infoBox.setText("Found DEF Boost!");
	}
	else
	{
		infoBox.setText("Your bag is full!");
	}
	infoBox.visible = true;
}

void MapScreen::update()
{
	//read user inputs including keyboard, mouse, gamepads, screen resize/close, touchscreens etc
	SDL_Event sdlEvent;
	//loop through input events and copy their details one by one into our sdlEvent variable
	while (SDL_PollEvent(&sdlEvent))
	{
		//event when user clicks close window button
		if (sdlEvent.type == SDL_QUIT)
		{
			quit = true;
		}
		//if a button was pressed
		if (sdlEvent.type == SDL_KEYDOWN)
		{
			//then check which button
			//did they press ESC key?
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				quit = true;
			}
			//hide infobox when space is pressed
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				infoBox.visible = false;
			}

			if (infoBox.visible == false && hero->getHP() > 0)
			{
				//player movement
				int hx = heroObj.x;
				int hy = heroObj.y;
				//right dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					hx++;
				}
				//left
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					hx--;
				}
				//down dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					hy++;
				}
				//up
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					hy--;
				}
				//if hx and hy are within the grid
				//AND is land we can walk in (map value of 1)
				if (hx >= 0 && hx <= 9 && hy >= 0 && hy <= 9 && map[hx][hy] == 1)
				{
					//set heroObn.x and y to hx and hy
					heroObj.x = hx;
					heroObj.y = hy;

					//can we escape the dungeon?
					if (!doorLocked && !escaped && heroObj.x == door.x && heroObj.y == door.y)
					{
						infoBox.setText("You escaped!");
						infoBox.visible = true;
						escaped = true;
					}

					//see if we walked onto a map objectl
					//for(int i = 1; i <= 10; i++)
					for (list<MapObject>::iterator mo = mapObjects.begin(); mo != mapObjects.end(); mo++)
					{
						//iterator is a special pointer pointing to a position in a list
						//dereferencing(*) iterator you access to the item at that point in the list

						//only interact with active map objects
						if ((*mo).active)
						{
							//is hero's x,y overlapping this mapobjects x.y
							if (heroObj.x == mo->x && heroObj.y == mo->y)
							{
								mo->active = false;

								//check map objects type and deal with accordingly
								if (mo->type == 3)
								{
									//TODO battle glob
								}
								if (mo->type == 4)
								{
									//TODO battle mimic
								}
								if (mo->type == 5)
								{
									//TODO open chest get item
									itemFound();
								}
							}
						}
					}
				}
				else
				{
					//invalid move, dont need to do anything here
				}
			}
		}
	}

	//check to see if map objects all inactive and if we should unlock the door
	if (!infoBox.visible && doorLocked)
	{
		bool monstersAlive = false;
		for (MapObject mo : mapObjects)
		{
			//if is a monster(glob or mimic)
			if (mo.type == 3 || mo.type == 4)
			{
				//if is active monster?
				if (mo.active) 
				{
					monstersAlive = true;
					break;
				}
			}
		}
		//if all monsters are dead, unlock the door
		if (!monstersAlive)
		{
			doorLocked = false;
			infoBox.setText("The door is unlocked!");
			infoBox.visible = true;
		}
	}

	//has user closed infobox after escaping
	if (!infoBox.visible && (escaped || hero->getHP() <= 0))
	{
		quit = true;
	}

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

	//DRAW MAP OBJECTS
	//draw hero
	tileRect.x = heroObj.x * tileRect.w; //e.g hero x = 4, y = 6. tile w = 32 h = 32
	tileRect.y = heroObj.y * tileRect.h;
	SDL_RenderCopy(renderer, heroTexture, NULL, &tileRect);
	//draw door
	tileRect.x = door.x * tileRect.w;
	tileRect.y = door.y * tileRect.h;
	SDL_RenderCopy(renderer, doorTexture, NULL, &tileRect);
	//DRAW MAP OBJECTS IN LIST
	//loop through list and draw each object
	for (MapObject mo : mapObjects)
	{
		//NOTE: mo is a mapObect copy from mapObjects and is not a direct reference to the mapOject
		if (mo.active)
		{
			tileRect.x = mo.x * tileRect.w;
			tileRect.y = mo.y * tileRect.h;
			if (mo.type == 3)//glob
			{
				SDL_RenderCopy(renderer, globTexture, NULL, &tileRect);
			}
			else//mimic or chest
			{
				SDL_RenderCopy(renderer, chestTexture, NULL, &tileRect);
			}
		}
	}

	//draw info box on top
	infoBox.draw();
}