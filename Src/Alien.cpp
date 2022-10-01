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
				
				if (i==0) 
					t.loadFromFile("images/block01.png"); 
				else if (i>0 && i<4) 
					t.loadFromFile("images/block02.png"); 
				else t.loadFromFile("images/block03.png");					
//				if (alienMoveFrameCounter==0) 
//					t.loadFromFile("images/block01.png");
//				else 
//					t.loadFromFile("images/block02.png");
				
				alien.setTexture(t);
				alien.setPosition(aliens[i][j].x,aliens[i][j].y);
		     	app.draw(alien);
			} 
    	}
}

void listAliens::move(){
	alienMoveCounter=alienMoveCounter-1;
	if (alienMoveCounter<=0) {
		alienMoveFrameCounter=alienMoveFrameCounter + 1;
		alienMoveFrameCounter=alienMoveFrameCounter % alienMoveNumFrames;
		if (aliensAtEdge()) {
			for (int i=0;i<alienRows;i++)
				for (int j=0; j<alienColumns; j++) {
					if (aliens[i][j].alive==true) {
						aliens[i][j].y=aliens[i][j].y+alienVertSpeed;
					}
				}
			alienDirection=-(alienDirection);
		}
		else {
			for (int i=0;i<alienRows;i++)
				for (int j=0; j<alienColumns; j++) {
					if (aliens[i][j].alive==true) {
						aliens[i][j].x=aliens[i][j].x+alienSpeed*alienDirection;
					}
				}
		}
		alienMoveCounter=alienMoveDelay;
	}
	
}

bool listAliens::aliensAtEdge() {
	for (int i=0;i<alienRows;i++)
			for (int j=0; j<alienColumns; j++) {
				if (aliens[i][j].alive==true) {
					if (alienDirection==1) {
						if ((aliens[i][j].x+alienSpeed)>alienMaxX) return true;
					}
					else 
						if ((aliens[i][j].x-alienSpeed)<alienMinX) return true;
				}
			}
	return false;
}




