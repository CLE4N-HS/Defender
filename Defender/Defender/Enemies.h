#pragma once
#include "Window.h"
#include "Bullets.h"


typedef enum {
	E_GODOWN,
	E_NATURAL,
	E_CHASE,
	E_MUTANT
}Enemy_state;

class Enemies
{
public:

	Enemies();

	virtual void update(Window& _window, sf::Vector2f _playerPos) = 0;
	virtual void display(Window& _window, bool _isMainView) = 0;

protected:
	virtual void addBullet(sf::Vector2f _pos) = 0;
	virtual void shouldMove(sf::Vector2f _centerView) = 0;

	sf::Vector2f pos;
	Enemy_state state;
	float attackTimer;
	sf::Vector2f velocity;

	std::list<Bullets *> bulletsList;
};


