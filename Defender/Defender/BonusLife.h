#pragma once
#include "Bonus.h"

class BonusLife : public Bonus
{
public:
	BonusLife(sf::Vector2f _pos);
	~BonusLife();

	inline int getLifeBonus() const { return m_lifeBonus; }

private:
	int m_lifeBonus;

};
