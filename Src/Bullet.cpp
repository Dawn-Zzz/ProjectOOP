#include "Bullet.h"

bulletShip::initBullet(){
	x=-20;
	y=-20;
}

void bulletShip::checkFire(playerShip a) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) 
		if (!active) {
			x=a.x+18;
			y=a.y-12;
			active=true;
	}
}

void bulletShip::move() {
	if (active) {
		y=y-speed;
		if (y<0) active=false;
	}
}

void bulletShip::draw(RenderWindow& app) {
	if (active) {
		RectangleShape bullet(sf::Vector2f(4, 16)); 
		bullet.setFillColor(Color::Red);
		bullet.setPosition(x,y);
		app.draw(bullet);
	}
}
bool bulletShip::checkCollisionAlien(Alien o2) {
	int object1Left=x;
	int object1Right=x+width-1;
	int object1Top=y;
	int object1Bottom=y+height-1;
	
	int object2Left=o2.x;
	int object2Right=o2.x+o2.width-1;
	int object2Top=o2.y;
	int object2Bottom=o2.y+o2.height-1;
	
	if ((object1Left < object2Right) && (object1Right > object2Left) 
	&& (object1Top < object2Bottom) && (object1Bottom > object2Top))
		return true;
	else
		return false;
}

void bulletShip::checkBulletCollisionsAlien(listAliens &a){
	bool bulletHasHitAlien=false;
	if (active) {
		for (int i=0;i<alienRows;i++)
			for (int j=0; j<alienColumns; j++) {
				if (a.aliens[i][j].alive==true) {
					bulletHasHitAlien = checkCollisionAlien(a.aliens[i][j]);
					if (bulletHasHitAlien) {
						a.aliens[i][j].alive = false;
						active = false;
						a.aliens[i][j].explosion=true;
						alienExplosion(i,j,a.aliens[i][j].x,a.aliens[i][j].y);
						if (maxMissile<5)
							maxMissile++;
						if (i==0) 
							score=score+20;
						else if (i>0 && i<4) 
							score=score+10; 
						else score=score+5;
					}
				}	
			}
	}
}



