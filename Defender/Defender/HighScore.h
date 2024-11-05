#pragma once
#include "Window.h"

class HighScore
{
public:
	HighScore();
	~HighScore();
	void addScore(int _score, std::string _name);
	void display();

private:
	std::vector<std::pair<int, std::string>> m_highScore;

};
