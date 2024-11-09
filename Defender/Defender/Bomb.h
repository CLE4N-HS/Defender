#pragma once
#include "Window.h"
#include "Enemies.h"
#include "Player.h"

class Bomb
{
public:
	Bomb();
	~Bomb();

	void update(Window& _window, std::list<Enemies*>& _enemies, Player& _player);

private:
	float m_timer;

};
