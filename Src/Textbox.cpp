#include "Textbox.h"

Textbox::Textbox(int size,sf::Color color, bool sel) {
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected=sel;
	if (sel) {
		textbox.setString("|");
	}
	else {
		textbox.setString("");
	}
}

void Textbox::setFont(sf::Font &font) {
	textbox.setFont(font);	
}

void Textbox::setPosition (sf::Vector2f pos) {
	textbox.setPosition (pos);	
}

void Textbox::setLimit (bool ToF) {
	hasLimit = ToF;
}

void Textbox::setLimit (bool ToF, int lim) {
	hasLimit = ToF;
	limit=lim;
}

void Textbox::setSelected (bool sel) {
	isSelected =sel;
	if (!sel) {
		std::string t = text.str();
		std::string newT = "";
		for (int i=0; i< t.length()-1;i++) {
			newT+=t[i];
		}
		textbox.setString(newT);
	}
}

void Textbox::draw (sf::RenderWindow &app) {
	app.draw (textbox);
}

void Textbox::typedOn (sf::Event input) {
	if (isSelected) {
		int charTyped = input.text.unicode;
		if (charTyped <128) {
			if (hasLimit) {
				if (text.str().length()<=limit) {
					inputLogic(charTyped);
				}
				else if (text.str().length()>limit && charTyped == DELETE_KEY) {
					deleteLastChar ();
				}
			}
			else {
				inputLogic(charTyped);
			}
		}
	}
}
