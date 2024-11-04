#pragma once
#include "Window.h"
#include "Particule.h"

class Bullets
{
public:
	Bullets();
	Bullets(sf::Vector2f _pos, sf::Vector2f _norDirection, sf::Vector2f _velocity);


	virtual void update(Window& _window, std::list<Particule*>& _particuleList) = 0;
	virtual void display(Window& _window) = 0;
	virtual sf::Vector2f getBulletPos() = 0;
	virtual sf::FloatRect getBulletColRect() = 0;
	virtual int getBulletId() = 0;

protected:

	sf::Vector2f pos;
	sf::Vector2f norDirction;
	sf::Vector2f velocity;
	sf::FloatRect colRect;

	int id;

};

