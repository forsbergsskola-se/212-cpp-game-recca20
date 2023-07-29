//extra library includes
#include <iostream> //input and output stream
#include <string>
#include "Puzzles.h"
#include "Character.h"
#include "Hero.h"
#include "Glob.h"
#include "Mimic.h"

using namespace std;

void main() {
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
	testCharacter.displayStats();

	//testCharacter2.hp = 22;
	Hero hero;
	hero.setName(name);
	hero.setupStats(hp, str, def, agi);

	Glob glob1;//calls constructor and fills in base stats

	hero.takeDamage(glob1.getDamage());
	glob1.displayStats();


	//lets user interact by pressing anykey
	system("pause");
}