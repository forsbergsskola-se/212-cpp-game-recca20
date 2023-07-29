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

	//lets user interact by pressing anykey
	system("pause");
}