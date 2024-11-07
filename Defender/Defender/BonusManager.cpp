#include "BonusManager.h"
#include "BonusSpeed.h"
#include "BonusBomb.h"
#include "BonusLife.h"

std::list<Bonus*> BonusManager::m_bonus;

BonusManager bonusManager;

BonusManager::BonusManager()
{
}

BonusManager::~BonusManager()
{
}

void BonusManager::createBonus(Bonus* _bonus, sf::Vector2f _pos)
{
}

void BonusManager::createRandomBonus(sf::Vector2f _pos)
{
	Bonus* randomBonus = nullptr;

	const int random = rand() % 100;
	if (random < 20)
		randomBonus = new BonusSpeed(_pos);
	else if (random < 40)
		randomBonus = new BonusBomb(_pos);
	else
		randomBonus = new BonusLife(_pos);

	m_bonus.push_back(randomBonus);
}

void BonusManager::eraseBonus(Bonus* _bonus)
{
	if (_bonus != nullptr)
	{
		for (std::list<Bonus*>::iterator it = m_bonus.begin(); it != m_bonus.end(); it++)
		{
			if (_bonus == *it)
			{
				// delete ??
				it = m_bonus.erase(it);
				return;
			}
		}
	}
}

void BonusManager::eraseBonuses()
{
	for (std::list<Bonus*>::iterator it = m_bonus.begin(); it != m_bonus.end();)
	{
		// delete ??
		it = m_bonus.erase(it);
	}
}

void BonusManager::update(Window& _window)
{
	for (std::list<Bonus*>::iterator it = m_bonus.begin(); it != m_bonus.end();)
	{
		(*it)->update(_window);

		if (!(*it)->isAlive())
		{
			// delete ??
			it = m_bonus.erase(it);
		}
		else
			it++;
	}
}

void BonusManager::display(Window& _window, const bool& mainView)
{
	for (std::list<Bonus*>::iterator it = m_bonus.begin(); it != m_bonus.end(); it++)
	{
		(*it)->display(_window, mainView);
	}
}

Bonus* BonusManager::getClosestBonus(sf::Vector2f _pos)
{
	float closestDistance = 10000000.f;
	Bonus* closestBonus = nullptr;
	for (std::list<Bonus*>::iterator it = m_bonus.begin(); it != m_bonus.end(); it++)
	{
		float distance = vec2fGetSqrtMagnitude(sf::Vector2f(_pos - (*it)->getPos()));
		if (distance < closestDistance)
		{
			closestBonus = *it;
			closestDistance = distance;
		}
	}

	return closestBonus;
}
