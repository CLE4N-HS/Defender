#pragma once
#include "Window.h"

class Particule
{
public:
	
	Particule();
	Particule(sf::Vector2f _pos, sf::Vector2f _viewPos, float _timeToDie);

	~Particule();

	void update(Window& _window);
	void display(Window& _window);

	float getTimerValue()const;

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_viewPos;
	float m_timeToDie;
};

