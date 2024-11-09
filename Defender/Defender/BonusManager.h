#pragma once
#include "Bonus.h"

class BonusManager
{
public:
	BonusManager();
	~BonusManager();
	static void createBonus(Bonus* _bonus, sf::Vector2f _pos);
	static void createRandomBonus(sf::Vector2f _pos);
	static void eraseBonus(Bonus* _bonus);
	static void eraseBonuses();

	static void update(Window& _window, sf::Vector2f _centerViewPos);
	static void display(Window& _window, const bool& mainView);

	static Bonus* getClosestBonus(sf::Vector2f _pos);

private:
	static std::list<Bonus*> m_bonus;

};
