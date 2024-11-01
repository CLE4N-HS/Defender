#include "enemiesBullets.h"
#include "textureManager.h"

enemiesBullets::enemiesBullets() : Bullets()
{

}

enemiesBullets::enemiesBullets(sf::Vector2f _pos, sf::Vector2f _norDirection, sf::Vector2f _velocity)
{
	pos = _pos;
	norDirction = _norDirection;
	velocity = _velocity;
}

enemiesBullets::~enemiesBullets()
{

}

void enemiesBullets::update(Window& _window)
{
	float delta = _window.getDeltaTime();

	norDirction = sf::Vector2f(norDirction.x * velocity.x * delta, norDirction.y * velocity.y * delta);
	pos += norDirction;
}

void enemiesBullets::display(Window& _window)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", "eBullet"));

	_window.rectangle.setPosition(pos);
	_window.rectangle.setSize(sf::Vector2f(12.f, 12.f));
	_window.rectangle.setOrigin(sf::Vector2f(6.f, 6.f));

	_window.draw(_window.rectangle);
}
