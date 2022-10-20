#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Variable.h"
#include "Ship.h"
#include "Alien.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class bulletShip:public Position,public Action {
	private:
		int speed=8;
		int height=12,width=4;
		bool active;
	public:
		initBullet();
		void checkFire(playerShip a);
		void move ();
		void draw (RenderWindow& app);
		bool checkCollisionAlien(Alien o2);
		void checkBulletCollisionsAlien(listAliens &a);
};

void drawScore();
#endif
