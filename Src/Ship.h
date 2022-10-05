#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "Variable.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class playerShip:public Position,public Action {
	private: 
		int xmax=980,xmin=0,speed=5;
		int width=42;
		int height=20;
		Sprite ship;
		Texture t1;
	public: 
		playerShip();
		void draw (RenderWindow& app);
		void move();
	
		friend class Bullet; 
		friend class missileAlien;
	//	friend bool checkCollisionShip(AlienMissile); 
};
#endif
