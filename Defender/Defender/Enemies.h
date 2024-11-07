#pragma once
#include "Window.h"
#include "Bullets.h"
#include "Player.h"
#include "civilians.h"


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

	virtual void update(Window& _window, Player _player, std::list<Bullets*>& _bulList) = 0;
	virtual void display(Window& _window, bool _isMainView) = 0;
	virtual sf::FloatRect getEnemyColRect() const = 0;
	virtual Enemy_state getEnemyState() const = 0;
	virtual void setEnemyState(Enemy_state _state) = 0;
	virtual void setEnemyTarget(civilians* _target) = 0;
	virtual sf::Vector2f getEnemyPos() const = 0;
	virtual bool isEnemyTarget() = 0;
	virtual void setVelocity(sf::Vector2f _vel) = 0;
	virtual civilians* getTargetedCivil() = 0;

protected:
	virtual void addBullet(sf::Vector2f _pos) = 0;
	virtual void shouldMove(sf::Vector2f _centerView) = 0;

	sf::Vector2f pos;
	Enemy_state state;
	float attackTimer;
	sf::Vector2f velocity;
	sf::FloatRect colRect;
	civilians* targetCivil;
};


