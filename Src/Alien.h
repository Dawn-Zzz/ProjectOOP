#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include "Variable.h"

#include <SFML/Graphics.hpp>

using namespace sf;

void alienExplosion(int, int, int, int);

class Explosion	{
	public:
	int explosionX=-20;
	int explosionY=-20;
	int ticCounter=0;
	int totalTics = 20;
};

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
		void drawExplosions(RenderWindow& app);
		bool aliensAtEdge();
	
		friend class bulletShip;
		friend class missileAlien; 
};

#endif
