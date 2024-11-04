#include "Particule.h"

Particule::Particule() : m_pos(), m_timeToDie()
{
}

Particule::Particule(sf::Vector2f _pos, float _timeToDie)
{
	m_pos = _pos;
	m_timeToDie = _timeToDie;
}

Particule::~Particule()
{

}

void Particule::update(Window& _window)
{
	float delta = _window.getDeltaTime();
	m_timeToDie -= delta;

}

void Particule::display(Window& _window)
{
	_window.rectangle.setTexture(nullptr);

	_window.rectangle.setPosition(m_pos);
	_window.rectangle.setSize(sf::Vector2f(12.f, 12.f));
	_window.rectangle.setOrigin(sf::Vector2f(6.f, 6.f));
	//_window.rectangle.setFillColor(sf::Color(255, 0, 0, 255));
	_window.draw(_window.rectangle,_window.getRenderState());
	
}

float Particule::getTimerValue() const
{
	return m_timeToDie;
}
