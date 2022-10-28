#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27	

class Textbox {
	public:
		Textbox() {	
		}
		Textbox(int size,sf::Color color, bool sel);
		void setFont(sf::Font &font);
		void setPosition (sf::Vector2f pos);
		void setLimit (bool ToF);
		void setLimit (bool ToF, int lim);
		void setSelected (bool sel);
		std::string getText() {
			return text.str();
		}
		void draw (sf::RenderWindow &app);
		void typedOn (sf::Event input);
	private:
		std::ostringstream text;
		sf::Text textbox;
		bool isSelected=false;
		bool hasLimit =false;
		int limit;
		
		void inputLogic (int charTyped) {
			if(charTyped!=DELETE_KEY && charTyped !=ENTER_KEY && charTyped !=ESCAPE_KEY) {
				text<<static_cast<char>(charTyped);
			}
			else if (charTyped == DELETE_KEY) {
				if (text.str().length()>0) {
					deleteLastChar();
				}
			}
			textbox.setString(text.str()+"|");
		}
		
		void deleteLastChar () {
			std::string t = text.str();
			std::string newT = "";
			for (int i=0; i< t.length()-1;i++) {
				newT+=t[i];
			}
			text.str("");
			text<<newT;
			textbox.setString(text.str());
		}
};

#endif
