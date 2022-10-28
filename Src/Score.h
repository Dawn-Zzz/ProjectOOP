#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Information {
	public:
		int HighScore;
		string Name;
};

class Score{
	private:
		Information infor[5];
		int currentScore;
		int Num=5;
	public:
		Score();
		void setCurrentScore();
		int getCurrentScore();

		void setLast(string name);
		void UpdateHighScore();
		
		int getBestScore();
		int getLastScore();
		
		void readFile();
		void writeFile();
		
		void draw(sf::RenderWindow &app);
};
