#ifndef MISSILE_H_INCLUDED
#define MISSILE_H_INCLUDED

#include "Variable.h"
#include "Ship.h"
#include "Alien.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class missileAlien:public Position,public Action{
	private:
		int speed=5;
		int height=20,width=4;
		bool active=false;
	public:
		initMissile();
		void move();
		void draw(RenderWindow& app); 
		void checkFire (listAliens a);
		bool checkCollisionShip(playerShip a);
		void checkBulletCollisionsShip(playerShip &ship);
};

#endif
