#include "playerBullets.h"
#include "textureManager.h"
#include "tools.h"

playerBullets::playerBullets() : Bullets()
{

}

playerBullets::playerBullets(sf::Vector2f _pos, sf::Vector2f _viewPos, sf::Vector2f _norDirection, sf::Vector2f _velocity)
{
	pos = _pos;
	viewPos = _viewPos;
	norDirction = _norDirection;
	velocity = _velocity;
	id = 0;
	m_timerEachParticule = 0.05f;
}

playerBullets::~playerBullets()
{

}

void playerBullets::update(Window& _window, std::list<Particule*>& _particuleList)
{
	float delta = _window.getDeltaTime();

	m_timerEachParticule -= delta;
	if (m_timerEachParticule <= 0.0f)
	{
  		_particuleList.push_back(new Particule(pos, _window.viewCurrentPos(pos), 0.2f));
		m_timerEachParticule = randFloat(0.001f, 0.02f);
	}

	pos += vec2fMultiplyVector(norDirction, vec2fMultiply(velocity, delta));
	viewPos += vec2fMultiplyVector(norDirction, vec2fMultiply(velocity, delta));
}

void playerBullets::display(Window& _window)
{
	_window.rectangle.setTexture(nullptr);

	_window.rectangle.setPosition(_window.viewDefaultPos(viewPos));
	_window.rectangle.setPosition(pos);
	_window.rectangle.setSize(sf::Vector2f(12.f, 12.f));
	_window.rectangle.setOrigin(sf::Vector2f(6.f, 6.f));
	_window.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
	colRect = sf::FloatRect(pos - _window.rectangle.getOrigin(), _window.rectangle.getSize());
	_window.draw(_window.rectangle, _window.getRenderState());
}

sf::Vector2f playerBullets::getBulletPos()
{
	return pos;
}

sf::FloatRect playerBullets::getBulletColRect()
{
	return colRect;
}

int playerBullets::getBulletId()
{
	return id;
}
