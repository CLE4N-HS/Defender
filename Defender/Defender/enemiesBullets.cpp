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
	id = 1;
}

enemiesBullets::~enemiesBullets()
{

}

void enemiesBullets::update(Window& _window, std::list<Particule*>& _particuleList)
{
	float delta = _window.getDeltaTime();

	//norDirction = sf::Vector2f(norDirction.x * velocity.x * delta, norDirction.y * velocity.y * delta);
	//norDirction = sf::Vector2f(norDirction.x * 100.f * delta, norDirction.y * 100.f * delta);
//	norDirction *= (100.f * delta);
	pos += vec2fMultiplyVector( norDirction, vec2fMultiply( velocity , delta));
}

void enemiesBullets::display(Window& _window)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", "eBullet"));

	_window.rectangle.setPosition(pos);
	_window.rectangle.setSize(sf::Vector2f(12.f, 12.f));
	_window.rectangle.setOrigin(sf::Vector2f(6.f, 6.f));
	colRect = sf::FloatRect(pos - _window.rectangle.getOrigin(), _window.rectangle.getSize());
	_window.draw(_window.rectangle);
}

sf::Vector2f enemiesBullets::getBulletPos()
{
	return pos;
}

sf::FloatRect enemiesBullets::getBulletColRect()
{
	return colRect;
}

int enemiesBullets::getBulletId()
{
	return id;
}
