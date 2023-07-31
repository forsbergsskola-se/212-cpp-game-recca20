# RPG Game (C++, SDL)


## Summary ## 
This game was developed as part of an assignment to learn and practice the fundamentals and some advance feature of c++, apply design patterns in game development using SDL. The game's premise revolves around an example of RPG scenario where the player finds themselves trapped in a cave, with the objective of surviving and escaping.

In order to achieve this goal, the player must explore the cave, searching for and collecting valuable items hidden within chests. These items likely serve as power-ups, resources, or tools to aid the player's survival and escape.

Overall, the game provides an opportunity for me to apply my C++ skills, utilize the SDL library, and learn about game development concepts such as game design, item management, and exploration in an RPG setting.


## Design Patterns ##
#### 1.Factory Pattern ####
In the character setup section, the code uses a factory-like pattern to create different types of characters (Berserker, Buff Nut, Speedy Ninja). Instead of creating character objects directly, it allows the player to choose a character type, and based on that choice, it sets up the character's stats accordingly. This pattern helps to encapsulate the character creation logic and provides a simple interface for creating different character instances.

#### 2.Observer Pattern 
The MapScreen class appears to be utilizing a form of the Observer pattern, where it listens for changes in the game world (player's movements, interactions, etc.) and updates the display accordingly. This pattern allows decoupling between the game logic (observable) and the graphical representation (observer), making it easier to manage and update the game state without directly affecting the rendering code.


## Noteworthy C++ Features 

#### 1.Runtime Polymorphism (Inheritance) ####
In the code, the concept of runtime polymorphism is demonstrated through the use of inheritance. The Character class serves as the base class, and the Hero and Glob classes are derived from it. This allows different character types to be represented and managed through a common interface, Character, while providing specific implementations for each derived class.

#### 2.Compile-Time Polymorphism (Function Overloading) #####
Compile-time polymorphism is demonstrated through function overloading. For example, the Character class has a member function called setupStats that is overloaded with different versions depending on the arguments provided. The appropriate version of the function is resolved at compile-time based on the number and types of arguments passed.

#### 3.Function Pointers ####
The concept of function pointers is relevant to the use of virtual functions for achieving runtime polymorphism. Virtual functions allow the derived classes (Hero and Glob) to override the base class's behavior and enable the correct function to be called based on the type of the object during runtime.

#### 4.Collections (Array) ####
The code uses an integer array named items to represent the player's inventory. The array holds information about different items, and the index of the array is used to identify different items (e.g., 0 represents no item, 1 represents chocolate, etc.).


## Challenges
Despite being new to C++ and having limited knowledge of smart pointers and SDL, I successfully tackled these challenges with the aid of various websites and recommendations from my superior, ultimately overcoming the obstacles and improving my understanding of design patterns and their application.


## Learnings
Through this assignment, I gained valuable insights into both fundamental and advanced aspects of C++, as well in game development using SDL. Over time, I started to understand the tasks more effectively., and the key lesson I took away from this experience is the importance of maintaining consistency in my approach and actions, which ultimately led to my successful learning and growth.


## Screenshots

#### Starting the game
![image](https://github.com/forsbergsskola-se/212-cpp-game-recca20/assets/45266094/a2eb301e-3e47-4988-9105-35c2648279c7)

#### Entering the dungeon
![image](https://github.com/forsbergsskola-se/212-cpp-game-recca20/assets/45266094/b8361478-9445-4e33-9b7e-cbd08aa7da68)

#### Found some item from the chest
![image](https://github.com/forsbergsskola-se/212-cpp-game-recca20/assets/45266094/0ed40a56-3ccf-4d1f-815a-58fdb10ebf93)

#### The door is unlocked message pops up
![image](https://github.com/forsbergsskola-se/212-cpp-game-recca20/assets/45266094/6d3bb319-c1d6-4b22-b662-3b699a5f826f)


## videos

#### video example of ganeplay player movement, loot item from chest. The battle with the monsters will be updating soon and the empty chest without loot is the mimic monster.

https://github.com/forsbergsskola-se/212-cpp-game-recca20/assets/45266094/c8192e7c-ea96-4f75-81ba-0e626ae5289b


## OBS!
The assignments is still in progress and keep updating time to time. There are a lot of features to be added in the future.

## Work progress

#### Done
Texture rendering,
Dungeon map,
User input and movement,
Infobox,
Get items from chest

#### To do
escape,
Battle screen start,
animation class,
Deltatime,
Animation manager,
character set animnation,
HP bar,
Battle button,
Punch face,
Battle Effects,
Item Menu,
Use Item.
