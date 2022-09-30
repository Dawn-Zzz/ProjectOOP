#include "Bullet.h"

bulletShip::bulletShip() {
	x=-20,y=-20;
}

void bulletShip::checkFire(playerShip a) {
	if (Keyboard::isKeyPressed(Keyboard::Up)) 
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
		RectangleShape bullet(sf::Vector2f(4, 20)); 
		bullet.setFillColor(Color::Green);
		bullet.setPosition(x,y);
		app.draw(bullet);
	}
}

