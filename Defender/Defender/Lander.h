#pragma once
#include "Enemies.h"

class Lander : public Enemies
{
public:

	Lander();

	void update(Window& _window, Player _player,std::list<Bullets*>& _bulList);
	void display(Window& _window, bool _isMainView);
	virtual sf::FloatRect getEnemyColRect() const;

private:
	void addBullet(sf::Vector2f _pos);
	void shouldMove(sf::Vector2f _centerView);

	float m_timerEachMoveY;
	float m_timerDuringMoveY;
	int m_directionX;
	int m_directionY;
};

