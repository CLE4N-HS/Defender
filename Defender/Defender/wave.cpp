#include "wave.h"
#include "Lander.h"
#include "textureManager.h"
#include "controller.h"

wave::wave() : m_textWawe()
{
	m_isScreenEndWawe = false;
	m_currentNbOfPlayer = 0;            // The current number of enemies on the map
	m_nbOfWantedEnemies = 10;			// The number of enemies wanted in this wave
	m_currentNbWave = 1;				// The current number of wave
	m_timerEachSpawn = 3.f;				// The timer between each enemy spawn
	m_timerSpawn = m_timerEachSpawn;	// The timer for each enemy spawn
}

void wave::update(Window& _window, std::list<Enemies*>& _enemyList, sf::Vector2f _pos)
{
	float delta = _window.getDeltaTime();

	if(!m_isScreenEndWawe) // Is the end wave screen is displayed 
	{
		if (m_currentNbOfPlayer >= m_nbOfWantedEnemies)
		{
			if (_enemyList.size() == 0)  // Is there any enemy on the map
			{
				m_isScreenEndWawe = true; // the screen must be displayed 
				m_currentNbOfPlayer = 0;  // So have to reinit each value
				m_currentNbWave++;
				m_timerEachSpawn -= 0.1f;
			}
		}
		else
		{
			m_timerSpawn -= delta;
			if (m_timerSpawn <= 0.0f)
			{
				_enemyList.push_back(new Lander(_pos, _window));
				m_currentNbOfPlayer++;
				m_timerSpawn = m_timerEachSpawn;
			}
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
			Gamepad_isButtonPressed(0, gamepadXBOX::A))
			m_isScreenEndWawe = false;
	}
}

void wave::display(Window& _window)
{
	if (m_isScreenEndWawe)
	{
		_window.rectangle.setTexture(nullptr);
		_window.rectangle.setPosition(sf::Vector2f(0.0f,0.0f));
		_window.rectangle.setSize(sf::Vector2f(1920.f,1080.f));
		_window.rectangle.setOrigin(sf::Vector2f(0.f, 0.f));
		_window.rectangle.setFillColor(sf::Color::Black);

		_window.draw(_window.rectangle);


		_window.text.setString("Wave " + std::to_string(m_currentNbWave) + " cleared !");
		_window.text.setPosition(_window.viewDefaultPos(sf::Vector2f(600.f, 400.f)));
		_window.text.setCharacterSize(100);

		_window.draw(_window.text);


		/*for (int i = 0; i < _numberOfCivilian; i++)
		{
			_window.rectangle.setTexture(tex_getTexture("all"));
			_window.rectangle.setTextureRect(tex_getAnimRect("all", "civilian"));
			_window.rectangle.setPosition(_window.viewCorrectPos(sf::Vector2f(200.f + static_cast<float>(i) * 20.f, 500.f),true));
			_window.rectangle.setSize(sf::Vector2f(12.f, 32.f));
			_window.rectangle.setOrigin(sf::Vector2f(6.f, 16.f));
			
			_window.draw(_window.rectangle);
		}*/
	}
}

