#include "DetectionPlayerBonus.h"
#include "BonusManager.h"
#include "BonusSpeed.h"
#include "BonusBomb.h"
#include "BonusLife.h"
#include "particleManager.h"

void DetectionPlayerBonus::detectCollision(Player& _player)
{
	sf::Vector2f playerPos = _player.getPos();
	Bonus* closestBonus = BonusManager::getClosestBonus(playerPos);

	if (closestBonus != nullptr)
	{
		if (closestBonus->getRect().intersects(_player.getRect()) && _player.getLife() > 0)
		{
			BonusSpeed* tmpBonusSpeed = dynamic_cast<BonusSpeed*>(closestBonus);
			BonusBomb* tmpBonusBomb = dynamic_cast<BonusBomb*>(closestBonus);
			BonusLife* tmpBonusLife = dynamic_cast<BonusLife*>(closestBonus);
			if (tmpBonusSpeed != nullptr)
			{
				_player.decreaseFirerate(tmpBonusSpeed->getSpeedBonus());
				_player.addScore(200);
				for (int i = 0; i < 10; i++)
				{
					prt_CreateSquareParticles(closestBonus->getPos(), 1, sf::Color(0, 208, 255), sf::Color(0, 208, 255, 0), 0.5f, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.f, 10.f), 0, 360, static_cast<float>(i + 10) * 2.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
				}
			}
			else if (tmpBonusBomb != nullptr)
			{
				_player.addBomb(tmpBonusBomb->getBombBonus());
				_player.addScore(150);
				for (int i = 0; i < 10; i++)
				{
					prt_CreateSquareParticles(closestBonus->getPos(), 1, sf::Color(255, 0, 42), sf::Color(255, 0, 42, 0), 0.5f, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.f, 10.f), 0, 360, static_cast<float>(i + 10) * 2.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
				}
			}
			else if (tmpBonusLife != nullptr)
			{
				_player.addLife(tmpBonusLife->getLifeBonus());
				_player.addScore(100);
				for (int i = 0; i < 10; i++)
				{
					prt_CreateSquareParticles(closestBonus->getPos(), 1, sf::Color(13, 255, 0), sf::Color(13, 255, 0, 0), 0.5f, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.f, 10.f), 0, 360, static_cast<float>(i + 10) * 2.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
				}
			}

			BonusManager::eraseBonus(closestBonus);
		}
	}

}
