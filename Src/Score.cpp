#include "Score.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Variable.h"

Score::Score(){
	//readFile();
	currentScore = 0;
	for (int i = 0; i < Num; i++) {
		infor[i].Name="NoName";
		infor[i].HighScore = 0;
	}
	//writeFile();
}

void Score::setCurrentScore(){
	currentScore = score;
}

int Score::getCurrentScore(){
	return currentScore;
}

void Score::UpdateHighScore(){
	for (int i=0;i<Num-1;i++)
		for (int j=Num-1;j>i;j--) {
			if (infor[j].HighScore>infor[j-1].HighScore){
				Information temp = infor[j];
				infor[j] =infor[j-1];
				infor[j-1]=temp;	
			}
		}
}

void Score::setLast(string name) {
	infor[Num-1].HighScore=score;
	infor[Num-1].Name=name;
}

int Score::getBestScore(){
	return infor[0].HighScore;
}

int Score::getLastScore() {
	return infor[Num-1].HighScore;
}

void Score::readFile(){
	std::ifstream input;
	input.open("HighScore.txt");
	for (int i=0; i<Num; i++) {
		input>>infor[i].HighScore;
		getline(input,infor[i].Name);
	}
	input.close();
}

void Score::writeFile(){
	std::ofstream output;
	output.open("HighScore.txt");
	for (int i=0; i<Num; i++) {
		output<<infor[i].HighScore;
		output<<infor[i].Name<<endl;
	}
	output.close();
}

void Score::draw(sf::RenderWindow &app) {
	readFile();
	sf::Font font;
	font.loadFromFile("font/upheavtt.ttf");
	for (int i=0; i<Num; i++) {
		std::stringstream s1,s2;
		sf::Text textInfor;
		textInfor.setFont(font);
		textInfor.setCharacterSize(50);
		textInfor.setStyle(sf::Text::Bold);
		textInfor.setFillColor(sf::Color::Red);
		s1 << infor[i].HighScore;
		textInfor.setString(s1.str());
		textInfor.setPosition(720,170+i*50);
		app.draw(textInfor);
		s2 << infor[i].Name;
		textInfor.setFillColor(sf::Color::White);
		textInfor.setString(s2.str());
		textInfor.setPosition(270,170+i*50);
		app.draw(textInfor);
	}
}

