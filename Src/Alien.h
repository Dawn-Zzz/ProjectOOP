#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include "Game.h"

#include <SFML/Graphics.hpp>

using namespace sf;
class Alien:public Position {
	public:
		bool alive;
		int height=20,width=42;
		bool explosion;
};

class listAliens {
	private:
		Alien aliens[alienRows][alienColumns];	
	public:
		initAliens ();
		void draw (RenderWindow& app);
		void move ();
		bool aliensAtEdge();
	
	//	friend void checkBulletCollisionsAlien(listAliens &a);
		friend class bulletShip;
	//	friend void drawExplosions();
		
	//	friend class AlienMissile; 
};

#endif
