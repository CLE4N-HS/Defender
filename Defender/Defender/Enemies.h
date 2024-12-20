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

	virtual void update(Window& _window, Player _player, std::list<Bullets*>& _bulList, bool _isCivilListEmpty) = 0;
	virtual void display(Window& _window, bool _isMainView) = 0;
	virtual sf::FloatRect getEnemyColRect() const = 0;
	virtual Enemy_state getEnemyState() const = 0;
	virtual void setEnemyState(Enemy_state _state) = 0;
	virtual void setEnemyTarget(civilians* _target) = 0;
	virtual sf::Vector2f getEnemyPos() const = 0;
	virtual bool isEnemyTarget() = 0;
	virtual void setVelocity(sf::Vector2f _vel) = 0;
	virtual civilians* getTargetedCivil() = 0;
	virtual bool getGrabbedCivil() = 0;
	virtual void setGrabbedCivil(bool _value) = 0;
	virtual void setNormVec(sf::Vector2f _normVec) = 0;
	virtual inline void resetTimerCatch() = 0;
	int getScoreValue();

protected:
	virtual void addBullet(sf::Vector2f _pos) = 0;
	virtual void shouldMove(sf::Vector2f _centerView) = 0;

	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::Vector2f normVec;
	Enemy_state state;
	float attackTimer;
	sf::FloatRect colRect;
	civilians* targetCivil;
	bool haveGrabbedCivil;
	int m_scoreValue;

};


