#include "Background.h"

backGround::backGround() {
	t3.loadFromFile("images/background.jpg");
	background.setTexture(t3);
}

void backGround::draw(RenderWindow& app) {
	app.draw(background);
}

