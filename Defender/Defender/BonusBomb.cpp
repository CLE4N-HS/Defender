#include "BonusBomb.h"

BonusBomb::BonusBomb(sf::Vector2f _pos) : Bonus(_pos), m_bombBonus(1)
{
	m_anim = "bomb";
}

BonusBomb::~BonusBomb()
{
}
