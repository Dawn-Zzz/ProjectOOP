#include "Alien.h"
int alienHorzSpacing = 150; //Khoang cach giua cac hang quai
int alienVertSpacing = 35; // Khoang cach giua cac cot quai
int alienTopOffset = 40; //Khoang cach giua quai voi thanh man hinh tren 
int alienDirection=1; 
int alienSpeed=12; //Toc do quai chay ngang 
int alienVertSpeed=12; //Khoang cach quai xuong dong 
int alienMaxX=980; int alienMinX=0; //Gioi han toa do quai di chuyen


//4 bien nay dung de delay toc do di chuyen cua quai
int alienMoveDelay=20;
int alienMoveCounter=alienMoveDelay;
int alienMoveNumFrames=2;
int alienMoveFrameCounter=0;

Explosion explosions[8][6];

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

void alienExplosion(int i, int j, int x, int y) {
	explosions[i][j].explosionX=x;
	explosions[i][j].explosionY=y;
}

void listAliens::drawExplosions(RenderWindow& app){
	for (int i=0;i<alienRows;i++)
		for (int j=0; j<alienColumns; j++) {
			if (aliens[i][j].explosion==true){
				Sprite e;
				Texture t;
				t.loadFromFile("images/block01.png");
				e.setTexture(t);
				e.setPosition(explosions[i][j].explosionX,explosions[i][j].explosionY);
				app.draw(e);
				explosions[i][j].ticCounter = explosions[i][j].ticCounter + 1;
				if (explosions[i][j].ticCounter > explosions[i][j].totalTics) {
					explosions[i][j].explosionX=-20;
					explosions[i][j].explosionY=-20;
				}
			}
		}
}



