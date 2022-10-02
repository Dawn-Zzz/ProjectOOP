#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include "Game.h"

#include <SFML/Graphics.hpp>

using namespace sf;

class Explosion	{
	public:
	int explosionX=-20;
	int explosionY=-20;
	int ticCounter=0;
	int totalTics = 20;
//	int baseSprite = 64,
//	int numFrames = 4;
};

void alienExplosion(int i, int j, int x, int y);

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
		void drawExplosions(RenderWindow& app);
		
	//	friend class AlienMissile; 
};

#endif
