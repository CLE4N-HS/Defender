#pragma once
#include "Bullets.h"

class enemiesBullets : public Bullets
{
public:
	enemiesBullets();
	enemiesBullets(sf::Vector2f _pos, sf::Vector2f _norDirection, sf::Vector2f _velocity);

	
	~enemiesBullets();
	void update(Window& _window, std::list<Particule*>& _particuleList);
	void display(Window& _window);;
	virtual sf::Vector2f getBulletPos();
	virtual sf::FloatRect getBulletColRect();
	virtual int getBulletId();


private:

};

