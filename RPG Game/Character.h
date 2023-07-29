#pragma once

#include <string>
#include <iostream>

using namespace std;

class Character
{
private:
	//attributes
	int hp, hpMax, str, def, agi;
public:
	Character();
	~Character();

	//behaviours/methods
	void setupStats(int _hp, int _str, int _def, int _agi);
	void displayStats();
};

