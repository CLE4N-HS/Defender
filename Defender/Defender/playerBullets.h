#pragma once
#include "Bullets.h"

class playerBullets : public Bullets
{

public:
	playerBullets();
	playerBullets(sf::Vector2f _pos, sf::Vector2f _viewPos, sf::Vector2f _norDirection, sf::Vector2f _velocity);


	~playerBullets();
	void update(Window& _window, std::list<Particule*>& _particuleList);
	void display(Window& _window);;
	virtual sf::Vector2f getBulletPos();
	virtual sf::FloatRect getBulletColRect();
	virtual int getBulletId();

private:
	float m_timerEachParticule;
};

