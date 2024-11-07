#pragma once
#include "Enemies.h"
#include "civilians.h"

class Detection
{
public:

	void update(std::list<Enemies *> _enemiesList, std::list<civilians *>& _civilList);

	civilians* getClosestCivil(std::list<civilians*> _civilList, sf::Vector2f _enemyPos);
private:


};

