#include "Game.h"
#include "Background.h"
#include "Ship.h"
#include "Bullet.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

RenderWindow app(VideoMode(1020, 600), "Galaxy");

class backGround;
class playerShip;
class bullet;

backGround Background;
playerShip Ship;
bulletShip Bullet_ship;

void shipFire () {
	Bullet_ship.checkFire(Ship);
	Bullet_ship.draw(app);
	Bullet_ship.move();
}

void Game::run()
{	
    srand(time(NULL));
   	app.setFramerateLimit(60);

    while (app.isOpen()){
    	Event e;
       	while (app.pollEvent(e)) {
        	if (e.type == Event::Closed)
            	app.close();
       		}
   		app.clear();
   		
   		//Xu ly
		Ship.move();
		shipFire();
		//Ve
		Background.draw(app);
		Ship.draw(app);
		Bullet_ship.draw(app);
		
	    app.display();
    }
}
