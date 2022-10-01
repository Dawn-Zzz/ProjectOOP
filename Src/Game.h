#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define alienRows 8 //So dong quai
#define alienColumns 6 //So cot quai 
int alienHorzSpacing = 150; //Khoang cach giua cac hang quai
int alienVertSpacing = 35; // Khoang cach giua cac cot quai
int alienTopOffset = 40; //Khoang cach giua quai voi thanh man hinh tren 
int alienDirection=1; 
int alienSpeed=12; //Toc do quai chay ngang 
int alienVertSpeed=12; //Khoang cach quai xuong dong 
int alienMaxX=980; int alienMinX=0; //Gioi han toa do quai di chuyen


//4 bien nay dung de delay toc do di chuyen cua quai
int alienMoveDelay=20;
int alienMoveCounter=alienMoveDelay;
int alienMoveNumFrames = 2;
int alienMoveFrameCounter = 0;

class Game {
	public:
		void run();
};

class Position {
	public:
		int x, y;
};

#endif
