#include "Enemies.h"


Enemies::Enemies()
{
	m_scoreValue = 0;
	pos = sf::Vector2f(500.f, 500.f);
	attackTimer = 0.f;
	state = E_NATURAL;
	velocity = sf::Vector2f(0.f,20.f);
}

int Enemies::getScoreValue()
{
	return m_scoreValue;
}
