#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;
class Button {
	public:
		Button();
		Button(string t, Vector2f size, int charSize, Color bgColor, Color textColor);
		
		void setFont(Font &font);
		void setBackColor(Color color);
		void setTextColor(Color color);
		void setPosition(Vector2f pos);
		void drawTo(RenderWindow &window);
		bool isMouseOver(RenderWindow &window);
	private:
		RectangleShape button;
		Text text;
};
