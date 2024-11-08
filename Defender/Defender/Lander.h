#pragma once
#include "Enemies.h"

class Lander : public Enemies
{
public:

	Lander();
	Lander(sf::Vector2f _pos, Window& _window);

	void update(Window& _window, Player _player,std::list<Bullets*>& _bulList, bool _isCivilListEmpty);
	void display(Window& _window, bool _isMainView);
	sf::FloatRect getEnemyColRect() const;
	virtual inline Enemy_state getEnemyState() const { return state; }
	virtual inline void setEnemyState(Enemy_state _state) { state = _state; }
	virtual inline void setEnemyTarget(civilians* _target) { targetCivil = _target;}
	virtual inline sf::Vector2f getEnemyPos() const { return pos; }
	virtual inline bool isEnemyTarget() { return targetCivil == nullptr ? false : true; }
	virtual inline void setVelocity(sf::Vector2f _vel) { velocity = _vel;}
	virtual inline civilians* getTargetedCivil() { return targetCivil; }
	virtual inline bool getGrabbedCivil() { return haveGrabbedCivil; }
	virtual inline void setGrabbedCivil() { haveGrabbedCivil = true; }
	virtual inline void setNormVec(sf::Vector2f _normVec) { normVec = _normVec; }


private:
	void addBullet(sf::Vector2f _pos);
	void shouldMove(sf::Vector2f _centerView);

	float m_timerEachMoveY;
	float m_timerDuringMoveY;
	float m_timerToCatch;
	int m_directionX;
	int m_directionY;
};

