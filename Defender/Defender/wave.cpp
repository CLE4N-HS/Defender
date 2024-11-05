#include "wave.h"
#include "Lander.h"

wave::wave() : m_textWawe()
{
	m_currentNbOfPlayer = 0;            // The current number of enemies on the map
	m_nbOfWantedEnemies = 10;			// The number of enemies wanted in this wave
	m_currentNbWave = 1;				// The current number of wave
	m_timerEachSpawn = 3.f;				// The timer between each enemy spawn
	m_timerSpawn = m_timerEachSpawn;	// The timer for each enemy spawn
}

void wave::update(Window& _window, std::list<Enemies*> _enemyList)
{
	float delta = _window.getDeltaTime();

	if(!m_isScreenEndWawe) // Is the end wave screen is displayed 
	{
		if (m_currentNbOfPlayer < m_nbOfWantedEnemies)
		{
			if (_enemyList.size() == 0)  // Is there any enemy on the map
			{
				m_isScreenEndWawe = true; // the screen must be displayed 
				m_currentNbOfPlayer = 0;  // So have to reinit each value
				m_currentNbWave++;
			}
		}
		else
		{
			m_timerSpawn -= delta;
			if (m_timerSpawn <= 0.0f)
			{
				_enemyList.push_back(new Lander());
				m_currentNbOfPlayer++;
				m_timerSpawn = m_timerEachSpawn;
			}
		}
	}
	else
	{

	}
}

void wave::display(Window& _window)
{
	if (m_isScreenEndWawe)
	{

	}
}
