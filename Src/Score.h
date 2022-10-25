#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>


class Score{
	private:
		int currentScore;
		int HighScore[5] ;
		int Num;
	public:
		Score();
		void setCurrentScore();
		int getCurrentScore();

		void UpdateHighScore();

		int getBestScore();

		void readFile();
		void writeFile();

		int* getHighScore();
		int getNum();

		void printScores();
};
