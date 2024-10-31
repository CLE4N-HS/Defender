#pragma once
#include "Window.h"


class Bullets
{
public:
	Bullets();
	Bullets(sf::Vector2f _pos, float _timeToDie);


	void update();
	void display();

private:

	sf::Vector2f m_pos;
	float m_timeToDie;

};

