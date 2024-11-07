#pragma once
#include "Enemies.h"


class wave
{
public:
	wave();

	void update(Window& _window, std::list<Enemies*>& _enemyList, sf::Vector2f _pos /*NbOfSavedPNJ*/);
	void display(Window& _window);

	inline bool isScreenWave() { return m_isScreenEndWawe; }

private:
	int m_currentNbWave;
	int m_currentNbOfPlayer;
	int m_nbOfWantedEnemies;

	float m_timerSpawn;
	float m_timerEachSpawn;
	
	bool m_isScreenEndWawe;

	sf::Text m_textWawe;
};

