#include "Bullets.h"

Bullets::Bullets() : m_pos()
{
	m_timeToDie = 0.0f;
}

Bullets::Bullets(sf::Vector2f _pos, float _timeToDie)
{
	m_pos = _pos;
	m_timeToDie = _timeToDie;
}

void Bullets::update()
{

}

void Bullets::display()
{

}
