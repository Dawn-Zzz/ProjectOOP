#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "Game.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class playerShip:public Position {
	private: 
		int xmax=980,xmin=0,speed=5;
		int width=48;
		int height=64;
		Sprite ship;
		Texture t1;
	public: 
		playerShip();
		void draw (RenderWindow& app);
		void move();
	
		friend class Bullet; 
	//	friend bool checkCollisionShip(AlienMissile); 
};
#endif
