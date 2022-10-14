#include "Missile.h"
int maxMissile=1;

missileAlien::initMissile(){
	x=-20;
	y=-20;
}

void missileAlien::draw(RenderWindow& app) {
	if (active) {
		RectangleShape missile(sf::Vector2f(4, 20)); 
		missile.setFillColor(Color::Yellow);
		missile.setPosition(x,y);
		app.draw(missile);
	}
}

void missileAlien::checkFire(listAliens a){
	int m = rand() % 8;
	int n = rand() % 6;
	if (a.aliens[m][n].alive==true) {
		if (!active) {
			x=a.aliens[m][n].x+24;
			y=a.aliens[m][n].y+10;
			active=true;
		}
	}
}

void missileAlien::move(){
	if (active) {
		y=y+speed;
		if (y>600) active=false;
	}
}

bool missileAlien::checkCollisionShip(playerShip a) {
	int object1Left=x;
	int object1Right=x+width-1;
	int object1Top=y;
	int object1Bottom=y+height-1;
	
	int object2Left=a.x;
	int object2Right=a.x+a.width-1;
	int object2Top=a.y;
	int object2Bottom=a.y+a.height-1;
	
	if ((object1Left < object2Right) && (object1Right > object2Left) 
	&& (object1Top < object2Bottom) && (object1Bottom > object2Top))
		return true;
	else
		return false;
}


void jumpToNewLifeState(){
	gameState = stateNewLife;
	timer = 0;
	playerLives = playerLives - 1;
}

void missileAlien::checkBulletCollisionsShip(playerShip &ship){
	bool bulletHasHitShip=false;
	if (active) {
		bulletHasHitShip = checkCollisionShip(ship);
		if (bulletHasHitShip) {
			active = false;
			ship.alive=false;
			jumpToNewLifeState();
		}	
	}
}


