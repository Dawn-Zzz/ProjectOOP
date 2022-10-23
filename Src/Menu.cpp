#include "Menu.h"
Button::Button() {
	
}

Button::Button(string t, Vector2f size, int charSize, Color bgColor, Color textColor) {
	text.setString(t);
	text.setColor(textColor);
	text.setCharacterSize(charSize);
	
	button.setSize(size);
	button.setFillColor(bgColor);
}

void Button::setFont(Font &font) {
	text.setFont(font);
}

void Button::setBackColor(Color color) {
	button.setFillColor(color);
}

void Button::setTextColor(Color color) {
	text.setColor(color);
}

void Button::setPosition(Vector2f pos) {
	button.setPosition(pos);
	float xPos = (pos.x + button.getLocalBounds().width / 3.2) - (text.getLocalBounds().width / 2);
	float yPos = (pos.y + button.getLocalBounds().height / 13) - (text.getLocalBounds().height / 2);
	text.setPosition({xPos, yPos});
}

void Button::setPosition2(Vector2f pos2) {
	button.setPosition(pos2);
	float xPos2 = (pos2.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
	float yPos2 = (pos2.y + button.getLocalBounds().height / 5) - (text.getLocalBounds().height / 2);
	text.setPosition({xPos2, yPos2});
}

void Button::drawTo(RenderWindow &window) {
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(RenderWindow &window) {
	float mouseX = Mouse::getPosition(window).x;
	float mouseY = Mouse::getPosition(window).y;
	
	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;
	
	float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;
	if(mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}
