#pragma once
#include "Bonus.h"

class BonusSpeed : public Bonus
{
public:
	BonusSpeed(sf::Vector2f _pos);
	~BonusSpeed();

	inline float getSpeedBonus() const { return m_speedBonus; }

private:
	float m_speedBonus;

};
