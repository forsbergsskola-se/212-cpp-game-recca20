#include "Character.h"



Character::Character() 
{
}


Character::~Character() 
{
}

void Character::setupStats(int _hp, int _str, int _def, int _agi) {
	hp = _hp;
	hpMax = _hp;
	str = _str;
	def = _def;
	agi = _agi;
}
void Character::displayStats() {
	cout << "hp: " << hp << "/" << hpMax << " str: " << str << " def: " << def << " agi: " << agi << endl;
}

