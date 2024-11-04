#pragma once
#include "Window.h"

class Particule
{
public:
	
	Particule();
	Particule(sf::Vector2f _pos, float _timeToDie);

	~Particule();

	void update(Window& _window);
	void display(Window& _window);

	float getTimerValue()const;

private:
	sf::Vector2f m_pos;
	float m_timeToDie;
};

