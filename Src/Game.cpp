#include "Game.h"
#include "Background.h"
#include "Ship.h"
#include "Bullet.h"
#include "Alien.h"
#include "Missile.h"
#include "Variable.h"
#include "Menu.h"
#include "Score.h"
#include "Textbox.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

RenderWindow app(VideoMode(1020, 600), "Galaxy");

class backGround;
class playerShip;
class bulletShip;
class listAliens;
class missileAlien;
class Score;

backGround Background;
playerShip Ship;
bulletShip Bullet_ship;
listAliens Aliens;
missileAlien Missile_alien[10];
Score a;

Action *pShip= new playerShip;
Action *pBullet_ship= new bulletShip;

Font fontMenu;
Font fontTextBox;
Font fontLoading;

Texture textureMenu;

Text loading;
Text nameGame;
Text subName;
Text overName;

Button btn1("PLAY", {200,50}, 30, Color::White, {229,88,96,250});
Button btn2("ABOUT", {200,50}, 30, Color::White, {229,88,96,250});
Button btn3("EXIT", {200,50}, 30, Color::White, {229,88,96,250});

SoundBuffer soundMenu;
SoundBuffer soundClick;

Sound sfx;
Sound sfx2;

Button btn_back("MAIN MENU", {200,50}, 30, Color::White, {229,88,96,250});
Button btn_overExit("EXIT", {200,50}, 30, Color::White, {229,88,96,250});

Button btn_submit ("SUBMIT",{200,50},30,Color::White, {229,88,96,250});

Textbox textbox1(40,sf::Color::White, true);

bool gameNeedsToBeInitialised=true;

int playerLives = 3;
int score=0;
int level=1;

int alienDeath=0;

int stateStartGame = 0;
int statePlayGame = 1;
int stateNewLife = 2;
int stateGameOver = 3;
int stateAllAliensDead = 4;
int gameState = stateStartGame;

int checkColor;
int checkColor2;

bool isPlaying = false;
bool isShowScore = false;
bool isOver = false;
bool isInput = false;

int timer=0;

void shipFire () {
	Bullet_ship.checkFire(Ship);
	Bullet_ship.draw(app);
	pBullet_ship->move();
}

void alienFire(){
	for (int i=0;i<maxMissile;i++) {
		Missile_alien[i].draw(app);
		Missile_alien[i].move();
		Missile_alien[i].checkFire(Aliens);
		Missile_alien[i].checkBulletCollisionsShip(Ship);
	}
}

void drawScore(){
	Font font;
	font.loadFromFile("font/upheavtt.ttf");
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setPosition(10,0);
	
	stringstream s1,s2;
	s1 << score;
	scoreText.setString("Score "+s1.str());
	app.draw(scoreText);

	Texture b,c;
	Sprite lives1,lives2,lives3;
	b.loadFromFile("images/heart.png");
	c.loadFromFile("images/loseheart.png");
	if(playerLives == 3){
		lives1.setTexture(b);
		lives1.setPosition(920,5);
		app.draw(lives1);
		lives2.setTexture(b);
		lives2.setPosition(950,5);
		app.draw(lives2);
		lives3.setTexture(b);
		lives3.setPosition(980,5);
		app.draw(lives3);
	}else if(playerLives == 2){
		lives1.setTexture(c);
		lives1.setPosition(920,5);
		app.draw(lives1);
		lives2.setTexture(b);
		lives2.setPosition(950,5);
		app.draw(lives2);
		lives3.setTexture(b);
		lives3.setPosition(980,5);
		app.draw(lives3);
	}else if(playerLives == 1){
		lives1.setTexture(c);
		lives1.setPosition(920,5);
		app.draw(lives1);
		lives2.setTexture(c);
		lives2.setPosition(950,5);
		app.draw(lives2);
		lives3.setTexture(b);
		lives3.setPosition(980,5);
		app.draw(lives3);
	}else if(playerLives == 0){
		lives1.setTexture(c);
		lives1.setPosition(920,5);
		app.draw(lives1);
		lives2.setTexture(c);
		lives2.setPosition(950,5);
		app.draw(lives2);
		lives3.setTexture(c);
		lives3.setPosition(980,5);
		app.draw(lives3);
	}
}

void initialiseGame(){
	playerLives = 3;
	score=0;
	maxMissile=1;
	Ship.initShip();
	Aliens.initAliens();
	Bullet_ship.initBullet();
	for (int i=0;i<maxMissile;i++) 
		Missile_alien[i].initMissile();
}

void playGame () {
	if (gameNeedsToBeInitialised) {
		pShip=&Ship;
		pBullet_ship=&Bullet_ship;
		initialiseGame();
		gameNeedsToBeInitialised = false;
	}
	//Ve
	Background.draw(app);
	Ship.draw(app);
	Bullet_ship.draw(app);
	Aliens.draw(app);
	Aliens.drawExplosions(app);
	drawScore();
   	//Xu ly
	pShip->move();
	shipFire();
	Bullet_ship.checkBulletCollisionsAlien(Aliens);
	Aliens.move();
	alienFire();
}

void newLife(){
	timer+=1;
	if (timer>180) {
		if (playerLives == 0) {
			gameState = stateGameOver;
			timer=0;
		}
		else {
			Ship.initShip();
			Bullet_ship.initBullet();
			for (int i=0;i<maxMissile;i++) {
				Missile_alien[i].initMissile();
			}
			maxMissile=1;
			gameState = statePlayGame;
		}
	}
	Aliens.move();
	Background.draw(app);
	Aliens.draw(app);
	Aliens.drawExplosions(app);
	drawScore();
}

void gameOver() {
	
	Background.draw(app);
	Font font;
	font.loadFromFile("font/upheavtt.ttf");
	a.readFile();
	a.setCurrentScore();
	stringstream s1,s2;
	Text currentScore;
	currentScore.setFont(font);
	currentScore.setCharacterSize(50);
	currentScore.setStyle(sf::Text::Bold);
	currentScore.setFillColor(sf::Color::Green);
	s1 << a.getCurrentScore();
	currentScore.setString("Your Score "+s1.str());
	currentScore.setPosition(345,270);
	app.draw(currentScore);
		
	Text bestscore;
	bestscore.setFont(font);
	bestscore.setCharacterSize(50);
	bestscore.setStyle(sf::Text::Bold);
	bestscore.setFillColor(sf::Color::Green);
	bestscore.setPosition(345,300);
	s2 << a.getBestScore();
	bestscore.setString("Best Score "+s2.str());
	app.draw(bestscore);
		
	Text over;
	over.setFont(font);
	over.setCharacterSize(50);
	over.setStyle(sf::Text::Bold);
	over.setFillColor(sf::Color::White);	
	over.setPosition(415,240);
	over.setString("You lose");
	app.draw(over);
	timer+=1;
	if (timer>180) {
		if (score>a.getLastScore() && isInput==false) {
			isInput= true;
		} 
		else {
			isPlaying = false;
			isOver = true;
			if	(isPlaying == false && isOver == true) {
				gameNeedsToBeInitialised = true;
				gameState = stateStartGame;
			}
		}
	}
}

void allAliensDead() {
	timer = timer + 1;
	Font font;
	font.loadFromFile("font/upheavtt.ttf");
	Text round;
	round.setFont(font);
	round.setCharacterSize(50);
	round.setStyle(sf::Text::Bold);
	round.setFillColor(sf::Color::White);	
	round.setPosition(415,270);
	stringstream s;
	
	Background.draw(app);
	Bullet_ship.draw(app);
	Ship.draw(app);
	Aliens.drawExplosions(app);
	drawScore();
	if (timer < 120) {	
		s << level;
		round.setString("Wave "+s.str());
		app.draw(round);
	} 
	else if (timer<180) {
		round.setString("Fight");
		app.draw(round);
	}
	else {
		Aliens.initAliens();
		gameState = statePlayGame;
	} 
	
	pShip->move();
	pBullet_ship->move();
	alienFire();	
}

void MenuRun() {
	
	soundMenu.loadFromFile("sounds/move_effect.wav");
	sfx.setBuffer(soundMenu);
	
	soundClick.loadFromFile("sounds/click-effect.wav");
	sfx2.setBuffer(soundClick);
	
	fontMenu.loadFromFile("font/upheavtt.ttf");
	
	textureMenu.loadFromFile("images/AmongUs.png");
	
	nameGame.setString("SPACE INVADERS");
	nameGame.setPosition({210,100});
	nameGame.setFont(fontMenu);
	nameGame.setCharacterSize(80);
	nameGame.setColor({244,208,104,250});
	
	subName.setString("Main menu");
	subName.setPosition({405,200});
	subName.setFont(fontMenu);
	subName.setCharacterSize(40);
	subName.setColor({244,208,104,200});

	btn1.setPosition({410, 300});
	btn1.setFont(fontMenu);
	
	btn2.setPosition({410, 400});
	btn2.setFont(fontMenu);
	
	btn3.setPosition({410, 500});
	btn3.setFont(fontMenu);
}

void MenuOver() {
	
	nameGame.setString("SPACE INVADERS");
	nameGame.setPosition({210,100});
	nameGame.setFont(fontMenu);
	nameGame.setCharacterSize(80);
	nameGame.setColor({244,208,104,250});
	
	overName.setString("Game over");
	overName.setPosition({405,200});
	overName.setFont(fontMenu);
	overName.setCharacterSize(40);
	overName.setColor({244,208,104,200});
	
	btn_back.setPosition2({410,350});
	btn_back.setFont(fontMenu);
	
	btn_overExit.setPosition2({410,450});
	btn_overExit.setFont(fontMenu);
}	

void TextBox() {
	textbox1.setFont(fontTextBox);
	textbox1.setPosition({248,200});
	textbox1.setLimit(true,25);
	btn_submit.setPosition2({410,450});
	btn_submit.setFont(fontMenu);
}

void Game::run()
{	
	MenuRun();
	Sprite sprite(textureMenu);
	
	Image icon;
	icon.loadFromFile("images/icon.png");
	app.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());
	
	fontLoading.loadFromFile("font/futureforcescondital.ttf");
	fontTextBox.loadFromFile("font/futureforcescondital.ttf");
	
	loading.setFont(fontLoading);
	loading.setFillColor(sf::Color::White);
	loading.setPosition(310, 200);
	loading.setCharacterSize(100);
	
	Clock load;
	load.restart();
	
    srand(time(NULL));
   	app.setFramerateLimit(60);
   	app.setKeyRepeatEnabled(true);
   	
    while(app.isOpen()) {
		Event Event;
		if(Keyboard::isKeyPressed(Keyboard::Return)) {
			
		}
		while (app.pollEvent(Event)) {
			if(Event.type == Event::Closed) 
				app.close();
		    if(isPlaying == false && isOver == false) {
		    	if (isShowScore) {
		    		switch(Event.type) {
			    		case Event::MouseMoved:
							//btn1
							if(btn_back.isMouseOver(app)) {
								btn_back.setBackColor({33,66,120,200});
								checkColor2 = 1;
								sfx.play();
							}
							else {
								btn_back.setBackColor(Color::White);
								checkColor = 0;
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor2 == 1) {
								//app.close();
								if(isPlaying == false) {
									sfx2.play();
									//gameState=statePlayGame;
									isShowScore = false;
								}
							}
						}
		    	} 
		    	else {
			    	switch(Event.type) {
			    		case Event::MouseMoved:
							//btn1
							if(btn1.isMouseOver(app)) {
								btn1.setBackColor({33,66,120,200});
								checkColor = 1;
								sfx.play();
							}
							else {
								btn1.setBackColor(Color::White);
								checkColor = 0;
							}
							//btn2
							if(btn2.isMouseOver(app)) {
								btn2.setBackColor({33,66,120,200});
								checkColor = 2;
								sfx.play();
							}
							else {
								btn2.setBackColor(Color::White);
		//						checkColor = 0;
							}
							//btn3
							if(btn3.isMouseOver(app)) {
								btn3.setBackColor({33,66,120,200});
								checkColor = 3;
								sfx.play();
							}
							else {
								btn3.setBackColor(Color::White);
		//						checkColor = 0;
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor == 1 && isPlaying == false) {
		//						app.close();
								sfx2.play();
								gameState=statePlayGame;
								isPlaying = true;
							}
							else if(Event.mouseButton.button == Mouse::Left && checkColor == 2) {
		//						check = 2;
								sfx2.play();
								isShowScore = true;
							}
							else if(Event.mouseButton.button == Mouse::Left && checkColor == 3) {
								sfx2.play();
								app.close();
							}
					}
				}
			}
			if(isOver == true) {
				if (isInput) {
					switch(Event.type) {
		    			case Event::MouseMoved:
						//btn1
							if(btn_submit.isMouseOver(app)) {
								btn_submit.setBackColor({33,66,120,200});
								checkColor2 = 1;
								sfx.play();
							}
							else {
								btn_submit.setBackColor(Color::White);
								checkColor = 0;
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor2 == 1) {
		//						app.close();
								if(isPlaying == false) {
									sfx2.play();
	//								gameState=statePlayGame;
									string name = textbox1.getText();
									a.setLast(name);
									a.UpdateHighScore();
									a.writeFile();
									isInput=false;
								}
							}
						case Event::TextEntered:
	        				textbox1.typedOn(Event);
					} 
				} 
				else {
			    	switch(Event.type) {
			    		case Event::MouseMoved:
							//btn1
							if(btn_back.isMouseOver(app)) {
								btn_back.setBackColor({33,66,120,200});
								checkColor2 = 1;
								sfx.play();
							}
							else {
								btn_back.setBackColor(Color::White);
								checkColor = 0;
							}
							//btn_over2
							if(btn_overExit.isMouseOver(app)) {
								btn_overExit.setBackColor({33,66,120,200});
								checkColor2 = 2;
								sfx.play();
							}
							else {
								btn_overExit.setBackColor(Color::White);
		//						checkColor = 0;
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor2 == 1) {
								//app.close();
								if(isPlaying == false) {
									sfx2.play();
									//gameState=statePlayGame;
									isOver = false;
								}
							}
							else if(Event.mouseButton.button == Mouse::Left && checkColor2 == 2) {
								sfx2.play();
								app.close();
							}
					}
				}
			}
		}
   		app.clear();
		if(isPlaying == true && isOver == false) {
			//Loading
			if (load.getElapsedTime().asSeconds() < 3) {
				loading.setString("Loading.");
				app.clear();
				//Background.draw(app);
				app.draw(loading);
				app.display();
				
				app.clear();
				//Background.draw(app);
				loading.setString("Loading...");
				app.draw(loading);
				app.display(); 
			}  
			else {
				//game play
		   		if (gameState==statePlayGame)
		   			playGame();
		   		else if (gameState==stateNewLife)
		   			newLife();
		   		else if (gameState==stateGameOver) 
		   			gameOver();
		   		else if (gameState==stateAllAliensDead)
					allAliensDead();
			}
	    app.display();
	    }
	    else if(isPlaying == false && isOver == false){
	    	if (isShowScore) {
	    		app.draw(sprite);
	    		btn_back.setPosition2({410,500});
				btn_back.setFont(fontMenu);
	    		btn_back.drawTo(app);
	    		app.display();
			}
			else {
			    app.draw(sprite);
			    app.draw(nameGame);
			    app.draw(subName);
				btn1.drawTo(app);
				btn2.drawTo(app);
				btn3.drawTo(app);
				app.display();
			}
		}	
		else if(isPlaying == false && isOver == true) {
			if (isInput) {
				TextBox();
				app.draw(sprite);
				textbox1.draw(app);
				btn_submit.drawTo(app);
				app.display();
			} 
			else {
				MenuOver();
				app.draw(sprite);
				app.draw(nameGame);
				app.draw(overName);
				btn_back.drawTo(app);
				btn_overExit.drawTo(app);
				app.display();
			}
		}
	}
}
