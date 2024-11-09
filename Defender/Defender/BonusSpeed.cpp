#include "BonusSpeed.h"

BonusSpeed::BonusSpeed(sf::Vector2f _pos) : Bonus(_pos), m_speedBonus(0.1f)
{
	m_anim = "speed";
}

BonusSpeed::~BonusSpeed()
{
}
