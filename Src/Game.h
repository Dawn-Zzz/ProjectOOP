#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define alienRows 8 //So dong quai
#define alienColumns 6 //So cot quai 
int alienHorzSpacing = 150; //Khoang cach giua cac hang quai
int alienVertSpacing = 35; // Khoang cach giua cac cot quai
int alienTopOffset = 40; //Khoang cach giua quai voi thanh man hinh tren 

int alienMoveFrameCounter=0;

class Game {
	public:
		void run();
};

class Position {
	public:
		int x, y;
};

#endif
