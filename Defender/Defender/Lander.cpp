#include "Lander.h"
#include "textureManager.h"

Lander::Lander() : Enemies()
{
}

void Lander::update(Window& _window)
{
	pos = sf::Vector2f(500.f, 500.f);
}

void Lander::display(Window& _window)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(sf::IntRect(441, 53, 36, 32));
	_window.rectangle.setPosition(pos);

	_window.draw(_window.rectangle);
}

void Lander::addBullet()
{
}
