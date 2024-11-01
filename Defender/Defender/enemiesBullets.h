#pragma once
#include "Bullets.h"

class enemiesBullets : public Bullets
{
public:
	enemiesBullets();
	enemiesBullets(sf::Vector2f _pos, sf::Vector2f _norDirection, sf::Vector2f _velocity);

	
	~enemiesBullets();
	void update(Window& _window);
	void display(Window& _window);
private:

};

