#include "Detection.h"
#include "tools.h"
#include "particleManager.h"

sf::Vector2f createVector22222(sf::Vector2f _pos1, sf::Vector2f _pos2);

civilians* getCivil(std::list<civilians*> _civilList, civilians* _civilTargeted)
{
	for (auto i = _civilList.begin(); i != _civilList.end();)
	{
		if ((*i) == _civilTargeted)
		{
			return (*i);
		}
		i++;
	}
	return nullptr;
	
}

void eraseCivil(std::list<civilians*>& _civilList, civilians* _civilTargeted)
{
	for (auto i = _civilList.begin(); i != _civilList.end();)
	{
		if ((*i) == _civilTargeted)
		{
			i = _civilList.erase(i);
		}
		else
			i++;
	}
}

void checkDeadByFalling(std::list<civilians*>& _civilList, Player _player)
{
	for (auto i = _civilList.begin(); i != _civilList.end();)
	{
		if ((*i)->getState() != C_FALL) { i++; continue; }

		if (vec2fGetMagnitude(createVector22222((*i)->getCivilPos(), _player.getPos())) < 100.f)
			(*i)->setState(C_GRABBED_BY_PLAYER);

		if ((*i)->getCivilPos().y > 980.f)
		{
			for (int o = 0; o < 10; o++)
			{
				prt_CreateSquareParticles((*i)->getCivilPos(), 1, sf::Color::White, sf::Color::Magenta, 0.5f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(10.f, 10.f), o * 36.f, o * 36.f, 200.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
			}
			i = _civilList.erase(i);
		}
		else
			i++;
	}
}


void Detection::update(std::list<Enemies*> _enemiesList, std::list<civilians*>& _civilList, Player _player)
{
	checkDeadByFalling(_civilList, _player);

	for (auto e = _enemiesList.begin(); e != _enemiesList.end();)
	{
		if ((*e)->getEnemyState() == E_CHASE) // Is it, in the chase state ?
		{
			sf::Vector2f tmpEPos = (*e)->getEnemyPos();
			if(!(*e)->isEnemyTarget() && _civilList.size() > 0)  // Is already targeted a civil ?
			{

				civilians* targetCivil = getClosestCivil(_civilList, tmpEPos);

				if (targetCivil != nullptr)
				{
					(*e)->setEnemyTarget(targetCivil);  // Now he's targetting a civil
				}
			}
			else if( (*e)->getTargetedCivil() != nullptr)// if he targeted a civil 
			{
				if (!(*e)->getGrabbedCivil()) // has he grabbed the civil ?
				{
					civilians* civilTargeted = getCivil(_civilList, (*e)->getTargetedCivil());
					sf::Vector2f tmpNormVectorE_C = createVector22222(tmpEPos, sf::Vector2f(civilTargeted->getCivilPos().x, civilTargeted->getCivilPos().y - 25.f));
					vec2fNormalize(tmpNormVectorE_C);
					(*e)->setNormVec(tmpNormVectorE_C);

					sf::Vector2f tmpVectorE_C = createVector22222(tmpEPos, sf::Vector2f(civilTargeted->getCivilPos().x, civilTargeted->getCivilPos().y - 25.f) );
					float tmp = vec2fGetSqrtMagnitude(tmpVectorE_C);
					if ( tmp < 100.f)
					{
						(*e)->setGrabbedCivil();
						civilTargeted->setCivilIsGrabbed(true);
					}

				}
				else // if he has already grabbed the civil
				{
					if (tmpEPos.y > 172.f + 16.f) // go up
					{

					}
					else // kill civil and become a mutant
					{
						eraseCivil(_civilList, (*e)->getTargetedCivil());
						(*e)->setEnemyState(E_MUTANT);
					}
				}
			}
		}
		e++;
	}
}

sf::Vector2f createVector22222(sf::Vector2f _pos1, sf::Vector2f _pos2)
{
	return sf::Vector2f(_pos2.x - _pos1.x, _pos2.y - _pos1.y);
}

civilians* Detection::getClosestCivil(std::list<civilians*> _civilList, sf::Vector2f _enemyPos)
{
	civilians* tmpCivil = nullptr;
	float lessDistance = 100000000.f;

	for (auto c = _civilList.begin(); c != _civilList.end();)
	{
		if ((*c)->getIsTargeted() == true) { c++; continue; }

		float tmpDistance = vec2fGetSqrtMagnitude(createVector22222(_enemyPos, (*c)->getCivilPos()));
		if (lessDistance > tmpDistance)
		{
			lessDistance = tmpDistance;
			tmpCivil = (*c);
		}
		c++;
	}

	if (lessDistance == 100000000.f)
		return nullptr;
	else
	{
		if(tmpCivil != nullptr)
			tmpCivil->setCivilIsTargeted(true);
		return tmpCivil;
	}
}
