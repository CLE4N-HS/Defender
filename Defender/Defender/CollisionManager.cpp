#include "CollisionManager.h"
#include "particleManager.h"

void CollisionManager::update(std::list<Bullets*>& _bulletsList, Player& _player, std::list<Enemies*>& _enemiesList)
{
	
	sf::Vector2f tmpPlayerPos = _player.getPos();
	for (std::list<Bullets*>::iterator it = _bulletsList.begin(); it != _bulletsList.end();)
	{
		if((*it)->getBulletId() == 1 )
		{
			if (_player.getLife() <= 0) { it++; continue; }

			sf::FloatRect tmpPlayerRect = _player.getRect();

			sf::Vector2f tmpBulletPos = (*it)->getBulletPos();
			sf::FloatRect tmpBulletRect = (*it)->getBulletColRect();


			if (tmpBulletPos.x < tmpPlayerPos.x - 1000.f || tmpBulletPos.x > tmpPlayerPos.x + 1000.f || tmpBulletPos.y < 162.f || tmpBulletPos.y > 1080.f)
				it = _bulletsList.erase(it);
			else if (tmpBulletRect.intersects(tmpPlayerRect))
			{
				_player.setDamage(100);
				if (_player.getLife() <= 0)
				{
					for (int i = 0; i < 100; i++)
					{
						prt_CreateSquareParticles(tmpPlayerPos, 1, sf::Color::White, sf::Color::White, 10.f, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.f, 10.f), 0, 360, i+10 * 10.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
						//prt_CreateSquareParticles(tmpPlayerPos, 1, sf::Color::White, sf::Color::White, 10.f, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.f, 10.f), 0, 360, i * 5.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
					}
				}
				it = _bulletsList.erase(it);
			}
			else
				it++;
		}






		else
		{
			sf::Vector2f tmpBulletPos = (*it)->getBulletPos();
			sf::FloatRect tmpBulletRect = (*it)->getBulletColRect();
			bool haveToChange = false;

			if (tmpBulletPos.x < tmpPlayerPos.x - 1000.f || tmpBulletPos.x > tmpPlayerPos.x + 1000.f)
				haveToChange = true;

			for (std::list<Enemies*>::iterator ite = _enemiesList.begin(); ite != _enemiesList.end();)
			{
				sf::FloatRect tmpEnemyRect = (*ite)->getEnemyColRect();
				
				if (tmpEnemyRect.intersects(tmpBulletRect))
				{
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
				it++;
		}
	}


}
