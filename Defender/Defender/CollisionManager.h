#pragma once
#include "tools.h"
#include "Bullets.h"
#include "Player.h"
#include "Enemies.h"

class CollisionManager
{
public:

	void update(std::list<Bullets*>& _bulletsList, Player& _player, std::list<Enemies*>& _enemiesList);

private:
};
