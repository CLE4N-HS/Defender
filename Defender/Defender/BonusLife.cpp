#include "BonusLife.h"

BonusLife::BonusLife(sf::Vector2f _pos) : Bonus(_pos), m_lifeBonus(1)
{
	m_anim = "life";
}

BonusLife::~BonusLife()
{
}
