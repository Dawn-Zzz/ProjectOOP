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

RenderWindow app(VideoMode(1020, 600), "Space Invaders");

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
Texture bgScore;

Text loading;
Text nameGame;
Text subName;
Text overName;
Text text1,text2;

Button btn1("PLAY", {200,50}, 30, Color::White, {229,88,96,250});
Button btn2("SCORE", {200,50}, 30, Color::White, {229,88,96,250});
Button btn3("EXIT", {200,50}, 30, Color::White, {229,88,96,250});

SoundBuffer soundMenu;
SoundBuffer soundClick;

Sound sfx;
Sound sfx2;

Button btn_back("MAIN MENU", {200,50}, 30, Color::White, {229,88,96,250});
Button btn_overExit("EXIT", {200,50}, 30, Color::White, {229,88,96,250});

Button btn_submit ("SUBMIT",{200,50},30,Color::White, {229,88,96,250});

Textbox textbox1(40,sf::Color::White, true);

RectangleShape rectangleLoading1,rectangleLoading2;

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

int checkColor;		//main menu
int checkColor2;	//over menu
int checkColor3;	//about menu

bool isPlaying = false;
bool isShowScore = false;
bool isOver = false;
bool isInput = false;

int timer=0;
int timeLoading=0;

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
	
	a.readFile();
	Text bestscore;
	bestscore.setFont(font);
	bestscore.setCharacterSize(30);
	bestscore.setStyle(sf::Text::Bold);
	bestscore.setFillColor(sf::Color::Green);
	bestscore.setPosition(400,0);
	s2 << a.getBestScore();
	bestscore.setString("Best Score "+s2.str());
	app.draw(bestscore);

	Texture heart,loseheart;
	Sprite lives;
	heart.loadFromFile("images/heart.png");
	loseheart.loadFromFile("images/loseheart.png");
	for (int i=3-playerLives; i<3; i++) {
		lives.setTexture(heart);
		lives.setPosition(920+i*30,5);
		app.draw(lives);
	}
	for (int i=0; i<3-playerLives; i++) {
		lives.setTexture(loseheart);
		lives.setPosition(920+i*30,5);
		app.draw(lives);
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
	currentScore.setCharacterSize(80);
	currentScore.setStyle(sf::Text::Bold);
	currentScore.setFillColor(sf::Color::Green);
	s1 << a.getCurrentScore();
	currentScore.setString("Your Score "+s1.str());
	currentScore.setPosition(220,280);
	app.draw(currentScore);
		
	Text over;
	over.setFont(font);
	over.setCharacterSize(80);
	over.setStyle(sf::Text::Bold);
	over.setFillColor(sf::Color::White);	
	over.setPosition(320,200);
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

void Loading () {
	loading.setString("Loading...");
	loading.setFont(fontLoading);
	loading.setFillColor(sf::Color::White);
	loading.setPosition(310, 200);
	loading.setCharacterSize(100);
	
    rectangleLoading1.setSize(sf::Vector2f(1000, 50));
    rectangleLoading1.setOutlineColor(sf::Color::White);
    rectangleLoading1.setFillColor(sf::Color::Cyan);
    rectangleLoading1.setOutlineThickness(5);
    rectangleLoading1.setPosition(10, 500);
    
    rectangleLoading2.setSize(sf::Vector2f(1000, 50));
    rectangleLoading2.setOutlineColor(sf::Color::White);
    rectangleLoading2.setOutlineThickness(5);
    rectangleLoading2.setPosition(10, 500);
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
	textbox1.setPosition({380,260});
	textbox1.setLimit(true,12);
	btn_submit.setPosition2({410,450});
	btn_submit.setFont(fontMenu);
	
	RectangleShape bgTextbox;
	bgTextbox.setSize({300, 40});
	bgTextbox.setPosition({360, 270});
	bgTextbox.setOutlineThickness(2);
    bgTextbox.setOutlineColor(sf::Color::Green);
    bgTextbox.setFillColor(sf::Color{0,0,255});
    app.draw(bgTextbox);
    
	text1.setFont(fontMenu);
	text1.setCharacterSize(50);
	text1.setStyle(sf::Text::Bold);
	text1.setFillColor(sf::Color{244,208,104,250});	
	text1.setPosition(250,100);
	text1.setString("YOUR SCORE IN TOP 5");
	app.draw(text1);
	
	text2.setFont(fontMenu);
	text2.setCharacterSize(30);
	text2.setStyle(sf::Text::Bold);
	text2.setFillColor(sf::Color{205,55,0});	
	text2.setPosition(330,150);
	text2.setString("PLEASE ENTER YOUR NAME");
	app.draw(text2);
}

void ShowHighScore(){
	Text highScore;
	Texture Item1,Item2,Item3,Item4, bg;
    Sprite Icon1,Icon2,Icon3,Icon4, bgScore;

	bg.loadFromFile("images/bgScore.png");
	bgScore.setTexture(bg);
	app.draw(bgScore);
	
	highScore.setString("LEADERBOARD");
	highScore.setPosition({250,40});
	highScore.setFont(fontMenu);
	highScore.setCharacterSize(80);
	highScore.setColor({244,208,104,250});
	app.draw(highScore);
	
	Item1.loadFromFile("images/Iconlb.png");
	Item2.loadFromFile("images/medalgold.png");
	Item3.loadFromFile("images/medalsilver.png");
	Item4.loadFromFile("images/medalbronze.png");
	for (int i=0; i<2; i++) {
		Icon1.setTexture(Item1);
		Icon1.setPosition(160+i*605,50);
		app.draw(Icon1);
	}
	Icon2.setTexture(Item2);
	Icon2.setPosition(220,190);
	app.draw(Icon2);
	Icon3.setTexture(Item3);
	Icon3.setPosition(220,240);
	app.draw(Icon3);
	Icon4.setTexture(Item4);
	Icon4.setPosition(220,290);
	app.draw(Icon4);
}

void Game::run()
{	
	MenuRun();
	Loading();
	Sprite sprite(textureMenu);
	
	Image icon;
	icon.loadFromFile("images/icon.png");
	app.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());
	
	fontLoading.loadFromFile("font/futureforcescondital.ttf");
	fontTextBox.loadFromFile("font/futureforcescondital.ttf");
	
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
								checkColor3 = 1;
								sfx.play();
							}
							else {
								btn_back.setBackColor(Color::White);
								checkColor3 = 0;
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor3 == 1) {
								if(isPlaying == false) {
									btn_back.setBackColor(Color::White);
									checkColor = 0;
									sfx2.play();
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
							}
							//btn3
							if(btn3.isMouseOver(app)) {
								btn3.setBackColor({33,66,120,200});
								checkColor = 3;
								sfx.play();
							}
							else {
								btn3.setBackColor(Color::White);
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor == 1 && isPlaying == false) {
								btn1.setBackColor(Color::White);
								sfx2.play();
								timeLoading=0;
								gameState=statePlayGame;
								isPlaying = true;
							}
							else if(Event.mouseButton.button == Mouse::Left && checkColor == 2) {
		//						check = 2;
								btn2.setBackColor(Color::White);
		    					checkColor3 = 0;
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
						checkColor2 = 0;
		    			case Event::MouseMoved:
						//btn1
							if(btn_submit.isMouseOver(app)) {
								btn_submit.setBackColor({33,66,120,200});
								checkColor2 = 1;
								sfx.play();
							}
							else {
								btn_submit.setBackColor(Color::White);
								checkColor2 = 0;
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor2 == 1) {
		//						app.close();
								if(isPlaying == false) {
									sfx2.play();
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
								checkColor2 = 0;
							}
							//btn_over2
							if(btn_overExit.isMouseOver(app)) {
								btn_overExit.setBackColor({33,66,120,200});
								checkColor2 = 2;
								sfx.play();
							}
							else {
								btn_overExit.setBackColor(Color::White);
							}
						case Event::MouseButtonReleased:
							if(Event.mouseButton.button == Mouse::Left && checkColor2 == 1) {
								//app.close();
								if(isPlaying == false) {
									checkColor = 0;
									sfx2.play();
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
			timeLoading+=1;
			if (timeLoading<90) {
				app.draw(loading);
				app.draw(rectangleLoading1);
				app.draw(rectangleLoading2);
				rectangleLoading2.move(sf::Vector2f(30,0));
			}  
			else {
				//game play
				timeLoading=90;
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
	    		ShowHighScore();
	    		btn_back.setPosition2({410,500});
				btn_back.setFont(fontMenu);
	    		btn_back.drawTo(app);
	    		a.draw(app);
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
				app.draw(sprite);
				TextBox();
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
