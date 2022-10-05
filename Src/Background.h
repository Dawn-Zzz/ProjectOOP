#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;
class backGround{
	private: 
		Sprite background;
		Texture t3;
	public: 
		backGround();
		void draw (RenderWindow& app);
};

#endif
