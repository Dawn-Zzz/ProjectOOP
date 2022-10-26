#include "Score.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Variable.h"

Score::Score(){
	//Num = 5;
	currentScore = 0;
	for (int i = 0; i < 5; i++) {
		HighScore[i] = 0;
	}
}

void Score::setCurrentScore(){
	currentScore = score;
}

int Score::getCurrentScore(){
	return currentScore;
}

void Score::UpdateHighScore(){
	//int s = currentScore;
	for (int i = 0; i < 5; i++) {
		if (currentScore > HighScore[i]) {
			std::swap(currentScore, HighScore[i]);
		}
	}
	std::sort(HighScore, HighScore + 5, [](int a, int b) { return a > b; });
}

int Score::getBestScore(){
	return HighScore[0];
}

void Score::readFile(){
	std::fstream input;
	input.open("HighScore.txt", std::ios::binary | std::ios::in);
	input.read((char*)HighScore, sizeof(HighScore));
	input.close();
}

void Score::writeFile(){
	std::fstream output;
	output.open("HighScore.txt", std::ios::binary | std::ios::out);
	output.write((char*)HighScore, sizeof(HighScore));
	output.close();
}

int* Score::getHighScore(){
	return HighScore;
}

//int Score::getNum(){
//	return Num;
//}

void Score::printScores(){
	for (int i = 0; i < 5; i++) {
		printf("%d ", HighScore[i]);
	}
	printf("\n");
}
