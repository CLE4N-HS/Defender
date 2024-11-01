#pragma once
#include "Window.h"


class Bullets
{
public:
	Bullets();
	Bullets(sf::Vector2f _pos, sf::Vector2f _norDirection, sf::Vector2f _velocity);


	virtual void update(Window& _window) = 0;
	virtual void display(Window& _window) = 0;

protected:

	sf::Vector2f pos;
	sf::Vector2f norDirction;
	sf::Vector2f velocity;

};

