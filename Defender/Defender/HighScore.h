#pragma once
#include "Window.h"
#include <iostream>

class HighScore
{
public:
	HighScore();
	~HighScore();
	static void addScore(int _score, std::string _name);
	static void save();
	static void display(Window& _window);

private:
	static std::vector<std::pair<int, std::string>> mycelium_highScore;
	static sf::Vector2f m_pos;
	//static HighScore m_h;

};