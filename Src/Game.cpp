#include "Game.h"
#include "Background.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

RenderWindow app(VideoMode(1020, 600), "Galaxy");

class backGround;

backGround Background;

void Game::run()
{	
    srand(time(NULL));
   	app.setFramerateLimit(60);

    while (app.isOpen()){
    	Event e;
       	while (app.pollEvent(e)) {
        	if (e.type == Event::Closed)
            	app.close();
       		}
   		app.clear();
		
		Background.draw(app);

	    app.display();
    }
}
