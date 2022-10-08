#include "Ship.h"

playerShip::initShip() {
	alive=true;
	x=470,y=530;
	t1.loadFromFile("images/ship.png");
	ship.setTexture(t1);
	ship.setPosition(x,y);
}

void playerShip::draw(RenderWindow& app) {
	if (alive==true) {
		app.draw(ship);
	}
}

void playerShip::move() {
	if (Keyboard::isKeyPressed(Keyboard::Right)) x=x+speed;
    if (Keyboard::isKeyPressed(Keyboard::Left)) x=x-speed;
    if (x<xmin) x=xmin; if (x>xmax) x=xmax;
    ship.setPosition(x,y);
}
