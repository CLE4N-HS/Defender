#pragma once
#include "Bonus.h"

class BonusBomb : public Bonus
{
public:
	BonusBomb(sf::Vector2f _pos);
	~BonusBomb();

	inline int getBombBonus() const { return m_bombBonus; }

private:
	int m_bombBonus;

};
