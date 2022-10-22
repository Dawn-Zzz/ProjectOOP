#include "Game.h"
#include "Background.h"
#include "Ship.h"
#include "Bullet.h"
#include "Alien.h"
#include "Missile.h"
#include "Variable.h"
#include "Score.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
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

Action *pShip= new playerShip;
Action *pBullet_ship= new bulletShip;

bool gameNeedsToBeInitialised=true;

int playerLives = 3;
int score=0;
int level=1;

int alienDeath=0;

int stateStartGame= 0;
int statePlayGame = 1;
int stateNewLife = 2;
int stateGameOver = 3;
int stateAllAliensDead = 4;
int gameState = statePlayGame;

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
	font.loadFromFile("upheavtt.ttf");
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setFillColor(sf::Color::Green);
	
	stringstream s1,s2;
	s1 << score;
	scoreText.setString("Score "+s1.str());
	app.draw(scoreText);
		
	Text lives;
	lives.setFont(font);
	lives.setCharacterSize(30);
	lives.setStyle(sf::Text::Bold);
	lives.setFillColor(sf::Color::Green);	
	lives.setPosition(890,0);
	s2 << playerLives;
	lives.setString("Lives "+s2.str());
	app.draw(lives);
	
//	Text bestscore;
//	Score a;
//	a.setCurrentScore();
//	a.readFile();
//	a.UpdateHighScore();
//	a.writeFile();
//	a.getCurrentScore();
//	a.getBestScore();
//	bestscore.setFont(font);
//	bestscore.setCharacterSize(30);
//	bestscore.setStyle(sf::Text::Bold);
//	bestscore.setFillColor(sf::Color::Green);
//	bestscore.setPosition(410,0);
//	s3 << a.getBestScore();
//	bestscore.setString("Best Score "+s3.str());
//	app.draw(bestscore);
}

void initialiseGame(){
	Ship.initShip();
	Aliens.initAliens();
	Bullet_ship.initBullet();
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
		if (playerLives == 0) 
			gameState = stateGameOver;
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
	Aliens.draw(app);
	drawScore();
	//timer+=1;
	Score a;
	//if (timer>80) {
	if (playerLives == 0){
		gameState = stateGameOver;
		app.clear();
		Background.draw(app);
		a.readFile();
		a.setCurrentScore();
		a.UpdateHighScore();
		a.writeFile();
		stringstream s1,s2;
		Font font;
		font.loadFromFile("upheavtt.ttf");//QuirkyRobot.ttf
		Text currentScore;
		currentScore.setFont(font);
		currentScore.setCharacterSize(50);
		currentScore.setStyle(sf::Text::Bold);
		currentScore.setFillColor(sf::Color::Green);
		s1 <<a.getCurrentScore();
//			text.setString("Your Score "+ss.str());
//			text.setPosition(345,290);
		currentScore.setString("Your Score "+s1.str());
		currentScore.setPosition(345,290);
		app.draw(currentScore);
		
		Text bestscore;
		bestscore.setFont(font);
		bestscore.setCharacterSize(50);
		bestscore.setStyle(sf::Text::Bold);
		bestscore.setFillColor(sf::Color::Green);
		bestscore.setPosition(345,320);
		s2 << a.getBestScore();
		bestscore.setString("Best Score "+s2.str());
		app.draw(bestscore);
		
		Text over;
		over.setFont(font);
		over.setCharacterSize(50);
		over.setStyle(sf::Text::Bold);
		over.setFillColor(sf::Color::White);	
		over.setPosition(415,260);
		over.setString("You Lose");
		app.draw(over);
		
			
	}
//	}
}


void allAliensDead() {
	timer = timer + 1;
	Font font;
	font.loadFromFile("QuirkyRobot.ttf");
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


void Game::run()
{	
	Font font;
	font.loadFromFile("futureforcescondital.ttf");
	Text loading;
	loading.setFont(font);
	loading.setFillColor(sf::Color::White);
	loading.setPosition(310, 200);
	loading.setCharacterSize(100);
	Clock load;
	load.restart();
    srand(time(NULL));
   	app.setFramerateLimit(60);
    while (app.isOpen()){
    	Event e;
       	while (app.pollEvent(e)) {
        	if (e.type == Event::Closed)
            	app.close();
       		}
   		//app.clear();
   			if (load.getElapsedTime().asSeconds() < 2) {
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
			if (gameState==statePlayGame)
   				playGame();
   			else if (gameState==stateNewLife)
   				newLife();
   			else if (gameState==stateGameOver)
   				gameOver();
//   		else if (gameState==stateGameOver)
//   			setCurrentScore();
   			else if (gameState==stateAllAliensDead)
				allAliensDead();
	    	app.display();
		     
	}
}
