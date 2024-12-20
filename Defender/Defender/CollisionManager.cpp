#include "CollisionManager.h"
#include "particleManager.h"
#include "BonusManager.h"
#include "Multiplication.h"

void resetTargetEnemy(std::list<Enemies*> _enemiesList, civilians* _civil)
{
	for (auto i = _enemiesList.begin(); i != _enemiesList.end();)
	{
		if (_civil == (*i)->getTargetedCivil())
		{
			(*i)->setEnemyTarget(nullptr);
			(*i)->setGrabbedCivil(false);
			(*i)->setEnemyState(E_NATURAL);
			(*i)->resetTimerCatch();
		}
		i++;
	}
}

void CollisionManager::update(std::list<Bullets*>& _bulletsList, Player& _player, std::list<Enemies*>& _enemiesList, std::list<civilians*>& _civilList)
{
	for (std::list<Enemies*>::iterator ite = _enemiesList.begin(); ite != _enemiesList.end();)
	{
		if (vec2fGetSqrtMagnitude(_player.getPos() - (*ite)->getEnemyPos()) > 500.f || _player.getLife() <= 0) { ite++; continue; }
		
		sf::FloatRect tmpERect = (*ite)->getEnemyColRect();
		sf::FloatRect tmpPRect =  _player.getRect();
		if (tmpERect.intersects(tmpPRect))
		{
			_player.setDamage(1);
		}
		ite++;
	}


	sf::Vector2f tmpPlayerPos = _player.getViewCenterPos();
	for (std::list<Bullets*>::iterator it = _bulletsList.begin(); it != _bulletsList.end();)
	{
		if((*it)->getBulletId() == 1 )
		{
			if (_player.getLife() <= 0) { it++; continue; }

			sf::FloatRect tmpPlayerRect = _player.getRect();

			sf::Vector2f tmpBulletPos = (*it)->getBulletPos();
			sf::FloatRect tmpBulletRect = (*it)->getBulletColRect();


			if (tmpBulletPos.x < tmpPlayerPos.x - 960.f || tmpBulletPos.x > tmpPlayerPos.x + 960.f || tmpBulletPos.y < 162.f || tmpBulletPos.y > 1080.f)
				it = _bulletsList.erase(it);

			else if (tmpBulletRect.intersects(tmpPlayerRect))
			{
				_player.setDamage(1);
				it = _bulletsList.erase(it);
			}
			else
				it++;
		}






		else // player bullets
		{
			sf::Vector2f tmpBulletPos = (*it)->getBulletPos();
			sf::FloatRect tmpBulletRect = (*it)->getBulletColRect();
			bool haveToChange = false;

			if (tmpBulletPos.x < tmpPlayerPos.x - 1000.f || tmpBulletPos.x > tmpPlayerPos.x + 1000.f)
			{
				Multiplication::resetMultiplication();
				haveToChange = true;
			}

			for (auto civil = _civilList.begin(); civil != _civilList.end();)
			{
				if (!(*civil)->getIsGrabbed()) { civil++; continue;}
				sf::Vector2f tmpCivilPos = (*civil)->getCivilPos();

				if (tmpBulletRect.intersects(sf::FloatRect(tmpCivilPos.x, tmpCivilPos.y, 12.f, 32.f)))
				{
					haveToChange = true;
					resetTargetEnemy(_enemiesList, *civil);
					civil = _civilList.erase(civil);
					Multiplication::resetMultiplication();
					for (int o = 0; o < 10; o++)
					{
						prt_CreateSquareParticles(tmpCivilPos, 1, sf::Color::White, sf::Color::Magenta, 0.5f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(10.f, 10.f), o * 36.f, o * 36.f, 200.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
					}
				}
				else
					civil++;

			}

			for (std::list<Enemies*>::iterator ite = _enemiesList.begin(); ite != _enemiesList.end();)
			{
				if (haveToChange) { ite++; continue; }
				sf::FloatRect tmpEnemyRect = (*ite)->getEnemyColRect();
				
				if (tmpEnemyRect.intersects(tmpBulletRect))
				{
					if (rand() % 5 == 0)
						BonusManager::createRandomBonus((*ite)->getEnemyPos());
					civilians* tmpCivil = (*ite)->getTargetedCivil();
					if(tmpCivil != nullptr)
					{
						if(tmpCivil->getIsGrabbed() == true)
							(*ite)->getTargetedCivil()->setState(C_FALL);
						(*ite)->getTargetedCivil()->setCivilIsTargeted(false);
						(*ite)->getTargetedCivil()->setCivilIsGrabbed(false);
					}
					if((*ite)->getEnemyState() == E_MUTANT)
					{
						for (int o = 0; o < 10; o++)
						{
							prt_CreateSquareParticles((*ite)->getEnemyPos(), 1, sf::Color::Green, sf::Color::Magenta, 0.5f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(10.f, 10.f), o * 36.f, o * 36.f, 200.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
						}
					}
					else
					{
						for (int o = 0; o < 10; o++)
						{
							prt_CreateSquareParticles((*ite)->getEnemyPos(), 1, sf::Color::White, sf::Color::Green, 0.5f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(10.f, 10.f), o * 36.f, o * 36.f, 200.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
						}
					}
					_player.addScore((*ite)->getScoreValue() * Multiplication::getMultiplication());
					Multiplication::addMultiplication(1);
					ite = _enemiesList.erase(ite);
					haveToChange = true;
				}
				else
					ite++;

			}
			if (haveToChange)
			{
				it = _bulletsList.erase(it);
			}
			else
			{
				it++;
			}
		}
	}


}
