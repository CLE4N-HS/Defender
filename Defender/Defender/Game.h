#pragma once
#include "State.h"
#include "Enemies.h"
#include "Player.h"
#include "Map.h"

class Game : public State
{
public:
	Game();
	virtual ~Game();
	virtual void update(Window& _window, State*& _state);
	virtual void display(Window& _window);

private:
	sf::Vector2f m_viewPos;
	std::list<Enemies*> enemiesList;
	Player m_player;
	Map m_map;
};
