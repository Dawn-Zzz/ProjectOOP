#include "Alien.h"

listAliens::initAliens() {
	for (int i=0;i<alienRows;i++)
		for (int j=0; j<alienColumns; j++) {
			aliens[i][j].x=j*alienHorzSpacing;
			aliens[i][j].y=alienTopOffset+i*alienVertSpacing;
			aliens[i][j].alive=true;
		//	aliens[i][j].explosion=false;
		//	alienBaseSprite = alienRowTypes[row].baseSprite;
		}	
}

void listAliens::draw(RenderWindow& app) {
	for (int i=0;i<alienRows;i++)
		for (int j=0; j<alienColumns; j++) {
			if (aliens[i][j].alive==true) {
				Sprite alien;
				Texture t;
//				if (alienMoveFrameCounter==0) 
//					t.loadFromFile("images/block05.png");
//				else 
					t.loadFromFile("images/block02.png");
				alien.setTexture(t);
				alien.setPosition(aliens[i][j].x,aliens[i][j].y);
		     	app.draw(alien);
			} 
    	}
}
