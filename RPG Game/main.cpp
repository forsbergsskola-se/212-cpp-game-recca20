//extra library includes
#include <iostream> //input and output stream
#include <string>

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



	//lets user interact by pressing anykey
	system("pause");
}