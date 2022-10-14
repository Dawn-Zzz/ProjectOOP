#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED
#define alienRows 8 //So dong quai
#define alienColumns 6 //So cot quai 
class Position {
	public:
		int x, y;
		Position(){
			x=-20;
			y=-20;
		}
};

class Action{
	public:
		virtual void move()=0;
};
extern int level;
extern int maxMissile;
extern int alienDeath;

extern int playerLives;
extern int score;

extern int stateStartGame;
extern int statePlayGame;
extern int stateNewLife;
extern int stateGameOver;
extern int stateAllAliensDead;
extern int gameState;

extern int timer;
#endif
