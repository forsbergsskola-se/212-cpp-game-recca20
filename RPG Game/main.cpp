//extra library includes
#include <iostream> //input and output stream
#include <string>
#include "Puzzles.h"
#include "Character.h"
#include "Hero.h"
#include "Glob.h"
#include "Mimic.h"
//SDL Libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

int main(int argc, char** argv) {
	//all of our starter code will start here

	//output hello world to the screen
	//cout = console out
	cout << "Hello there...." << endl; //endl = end line
	cout << "What is your name?" << endl;
	//variable to hold name of user/player
	//format of declaring a variable: datatype variableName;
	string name;
	//read name into name variable from keyboard
	//cin = console in
	cin >> name;

	cout << "Welcome to the dungeon " << name << ", mwaahahahaha!!!" << endl;

	cout << "How old are you?" << endl;
	int age;
	cin >> age;
	cout << "So you are " << age << " years old!" << endl;

	cout << "What is your favourite number: " << endl;
	int favNum;
	cin >> favNum;
	cout << "Well you are now stuck in this dungeon for " << favNum << " years! Mwahahahah!" << endl;

	//working out the new age
	int newAge = age + favNum;
	cout << "Its time to escape before you turn " << newAge << " years old!" << endl;

	//output earning of they'll be 80 or older
	if (newAge >= 80)
	{
		cout << "You might now even live to this age!" << endl;
	}

	//if favNum is equal to 64 then output message
	if (favNum == 64) {
		cout << "Nice favourite number by the way!" << endl;
	}


	//hero stats
	int hp = 0, str = 0, def = 0, agi = 0;

	bool characterSetup = false;

	while (characterSetup == false)
	{
		cout << "What type of character are you?" << endl;
		cout << "1 - Berserker" << endl;
		cout << "2 - Buff Nut" << endl;
		cout << "3 - Speedy Ninja" << endl;
		int choice;
		cin >> choice;
		if (choice == 1){
			hp = 60;
			str = 10;
			def = 2;
			agi = 3;
		}
		else if (choice == 2) {
			hp = 100;
			str = 4;
			def = 5;
			agi = 1;
		}
		else if (choice == 3) {
			hp = 80;
			str = 3;
			def = 1;
			agi = 10;
		}
		else
		{
			cout << "Invalid choice! Try again..." << endl;
		}

		if (choice >= 1 && choice <= 3)
		{
			characterSetup = true;
		}
	}

	cout << "stats" << endl;
	cout << "hp: " << hp << endl;
	cout << "strength: " << str << endl;
	cout << "defense: " << def << endl;
	cout << "agility: " << agi << endl;

	cout << "The first gate is opening, counting down..." << endl;
	//	setup;	condition;	incrementer/decrementer
	for (int i = 10; i >= 0; i--)
	{
		cout << i << "..." << endl;
	}

	//intro to functions
	cout << "In the first room stands a tall slender fugure in a cloak." << endl;
	cout << "Totally skull faced. He speaks:" << endl;
	cout << "I will ask you 3 questions with varuous punishments if you get them wrong..." << endl;
	int dmg = puzzle1() + puzzle2(str, agi) + puzzle3(name);

	hp = hp - dmg;
	cout << "You are inflicted " << dmg << " amount of damage! Your HP is now " << hp << endl;

	//build an object of class type Character
	Character testCharacter;
	testCharacter.setupStats(hp, str, def, agi);
	testCharacter.displayStats();

	Character testCharacter2;
	testCharacter2.setupStats(2343, 23, 34, 23);
	testCharacter2.displayStats();

	//testCharacter2.hp = 22;
	Hero hero;
	hero.setName(name);
	hero.setupStats(hp, str, def, agi);

	Glob glob1;//calls constructor and fills in base stats

	hero.takeDamage(glob1.getDamage());
	glob1.takeDamage(hero.getDamage());

	hero.displayStats();
	glob1.displayStats();
	glob1.makeDumbNoise();

	//class object pointers
	Glob* globPtr = new Glob();
	(*globPtr).displayStats();
	globPtr->takeDamage(3453);
	globPtr->displayStats();
	globPtr->makeDumbNoise();

	delete globPtr;
	globPtr = NULL;

	if (globPtr != NULL) 
		cout << "glob ptr pointing to something" << endl;
	else
		cout << "glob is dead!!!" << endl;

	//POLYMORPHISM
	//reference glob as a character(treat child like parent)
	Character* charPtr = &glob1;
	charPtr->takeDamage(-5678);
	charPtr->displayStats();
	//casting
	Glob* globPtr2 = (Glob*)charPtr;
	globPtr2->makeDumbNoise();

	//Initialise SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//if init not return 0, then initialisation failed
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}

	//initialise subsystems we need e.g sdl image, mixer, ttf
	//TODO: look up c++ bitwise logic
	//image- being able to deal with other image types other then bmp. Also lets you play with surface pixel data
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		cout << "SDL IMG Init Error: " << IMG_GetError() << endl;
		system("pause");
		return 1;
	}
	//ttf - text to font, for rendering text to screen
	if (TTF_Init() != 0)
	{
		cout << "SDL TTF Init Error: " << TTF_GetError() << endl;
		system("pause");
		return 1;
	}
	//mixer- sound and music
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "SDL Mixer Init Error: " << Mix_GetError() << endl;
		system("pause");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("RPG GAME!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "SDL window Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}
	

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "SDL renderer Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	//the size gfx are at min, but then scale up to actual window size
	SDL_RenderSetLogicalSize(renderer, 320, 240);

	//load up image file and store as Testure inside of gfx card VRAM
	SDL_Texture* testImg = IMG_LoadTexture(renderer, "assets/girlIdle.png");
	if (testImg == NULL)
	{
		cout << "Image did not load! " << IMG_GetError() << endl;
	}

	bool keepLooping = true;
	//Game Loop
	while (keepLooping)
	{



		SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);//RGB
		//clear entire screen with current draw colour
		SDL_RenderClear(renderer);

		SDL_Rect rect;
		rect.x = 10;
		rect.y = 10;
		rect.w = 50;
		rect.h = 50;
		SDL_SetRenderDrawColor(renderer, 34, 76, 22, 255);
		//draws filled in rectangle to window using rectangles data
		SDL_RenderFillRect(renderer, &rect);

		//the region of the texture we want to draw from
		SDL_Rect srcRect;
		srcRect.x = 20;
		srcRect.y = 50;
		srcRect.w = 55;
		srcRect.h = 75;

		//texture destination rectangle
		SDL_Rect destRect;
		destRect.x = 70;
		destRect.y = 20;
		destRect.w = 700;
		destRect.h = 137;

		//renderCopy renders textures to the window
		SDL_RenderCopy(renderer, testImg, &srcRect, &destRect);

		//swaps drawing buffer
		SDL_RenderPresent(renderer);

		//ticks are milliseconds since the start of SDL init
		if (SDL_GetTicks() > 5000)//1000ms = 1 second
		{
			keepLooping = false;
		}

	}
	//Clean Up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	//lets user interact by pressing anykey
	system("pause");
	return 0;
}