#include "DetectionPlayerBonus.h"
#include "BonusManager.h"
#include "BonusSpeed.h"
#include "BonusBomb.h"
#include "BonusLife.h"

void DetectionPlayerBonus::detectCollision(Player& _player)
{
	sf::Vector2f playerPos = _player.getPos();
	Bonus* closestBonus = BonusManager::getClosestBonus(playerPos);

	if (closestBonus != nullptr)
	{
		if (closestBonus->getRect().intersects(_player.getRect()))
		{
			BonusSpeed* tmpBonusSpeed = dynamic_cast<BonusSpeed*>(closestBonus);
			BonusBomb* tmpBonusBomb = dynamic_cast<BonusBomb*>(closestBonus);
			BonusLife* tmpBonusLife = dynamic_cast<BonusLife*>(closestBonus);
			if (tmpBonusSpeed != nullptr)
			{
				_player.decreaseFirerate(tmpBonusSpeed->getSpeedBonus());
			}
			else if (tmpBonusBomb != nullptr)
			{
				_player.addBomb(tmpBonusBomb->getBombBonus());
			}
			else if (tmpBonusLife != nullptr)
			{
				_player.addLife(tmpBonusLife->getLifeBonus());
			}

			BonusManager::eraseBonus(closestBonus);
		}
	}

}
