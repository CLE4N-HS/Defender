#pragma once
#include "Window.h"
#include "Bullets.h"


typedef enum {
	E_NATURAL,
	E_CHASE,
}Enemy_state;

class Enemies
{
public:

	Enemies();

	virtual void update(Window& _window) = 0;
	virtual void display(Window& _window) = 0;

protected:
	virtual void addBullet() = 0;

	sf::Vector2f pos;
	Enemy_state state;
	float attackTimer;

};


