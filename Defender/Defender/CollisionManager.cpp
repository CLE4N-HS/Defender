#include "CollisionManager.h"
#include "BonusManager.h"

void CollisionManager::update(std::list<Bullets*>& _bulletsList, Player& _player, std::list<Enemies*>& _enemiesList)
{
	
	sf::Vector2f tmpPlayerPos = _player.getPos();
	for (std::list<Bullets*>::iterator it = _bulletsList.begin(); it != _bulletsList.end();)
	{
		if((*it)->getBulletId() == 1)
		{
			sf::FloatRect tmpPlayerRect = _player.getRect();

			sf::Vector2f tmpBulletPos = (*it)->getBulletPos();
			sf::FloatRect tmpBulletRect = (*it)->getBulletColRect();


			if (tmpBulletPos.x < tmpPlayerPos.x - 1000.f || tmpBulletPos.x > tmpPlayerPos.x + 1000.f || tmpBulletPos.y < 162.f || tmpBulletPos.y > 1080.f)
				it = _bulletsList.erase(it);
			else if (tmpBulletRect.intersects(tmpPlayerRect))
			{
				_player.setDamage(10);
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
					//if (rand() % 5 == 0)
					//	BonusManager::createRandomBonus((*ite)->getPos());

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
