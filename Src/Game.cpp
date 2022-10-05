#include "Game.h"
#include "Background.h"
#include "Ship.h"
#include "Bullet.h"
#include "Alien.h"
#include "Missile.h"
#include "Variable.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

RenderWindow app(VideoMode(1020, 600), "Galaxy");

class backGround;
class playerShip;
class bulletShip;
class listAliens;
class missileAlien;

backGround Background;
playerShip Ship;
bulletShip Bullet_ship;
listAliens Aliens;
missileAlien Missile_alien[6];

Action *pShip= new playerShip;
Action *pBullet_ship= new bulletShip;

void shipFire () {
	Bullet_ship.checkFire(Ship);
	Bullet_ship.draw(app);
	pBullet_ship->move();
}

void alienFire(){
	for (int i=0;i<n;i++) {
		Missile_alien[i].draw(app);
		Missile_alien[i].move();
		Missile_alien[i].checkFire(Aliens);
		Missile_alien[i].checkBulletCollisionsShip(Ship);
	}
}

void drawScore(){
	Font font;
	font.loadFromFile("QuirkyRobot.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Green);
	stringstream ss;
//	ss << Bullet_ship.score;
	ss << die;
	text.setString("Score "+ss.str());
	app.draw(text);		
}

void Game::run()
{	
    srand(time(NULL));
   	app.setFramerateLimit(60);
	Aliens.initAliens();
	pShip=&Ship;
	pBullet_ship=&Bullet_ship;
    while (app.isOpen()){
    	Event e;
       	while (app.pollEvent(e)) {
        	if (e.type == Event::Closed)
            	app.close();
       		}
   		app.clear();
   		
		//Ve
		Background.draw(app);
		Ship.draw(app);
		Bullet_ship.draw(app);
		Aliens.draw(app);
		Aliens.drawExplosions(app);
		drawScore();
   		//Xu ly
		pShip->move();
		shipFire();
		Bullet_ship.checkBulletCollisionsAlien(Aliens);
	//	Aliens.move();
		alienFire();
	    app.display();
    }
}
