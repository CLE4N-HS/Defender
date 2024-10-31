#pragma once
#include "Window.h"

class Map
{
public:
	Map();
	~Map();

	void update(Window& _window, sf::Vector2f _playerPos);
	void display(Window& _window, bool mainView, sf::Vector2f _playerPos);

private:
	sf::Vector2f m_pos1;
	sf::Vector2f m_pos2;

};
