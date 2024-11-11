#include "wave.h"
#include "Lander.h"
#include "textureManager.h"
#include "controller.h"
#include "soundManager.h"

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
				sound_play("nextWave");
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

void wave::display(Window& _window, int _numOfCivilAlive)
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
		_window.text.setPosition(_window.viewDefaultPos(sf::Vector2f(1000.f, 400.f)));
		sf::Vector2f tmpPos = _window.text.getPosition();
		_window.text.setCharacterSize(100);
		_window.textCenterOrigin();

		_window.draw(_window.text);


		for (int i = 0; i < _numOfCivilAlive; i++)
		{
			_window.rectangle.setTexture(tex_getTexture("all"));
			_window.rectangle.setTextureRect(tex_getAnimRect("all", "civilian"));
			_window.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
			float size = 2.f;
			_window.rectangle.setPosition(_window.viewDefaultPos(sf::Vector2f(800.f + 20.f * size * i, 550.f)));
			sf::Vector2f pos = _window.rectangle.getPosition();
			_window.rectangle.setSize(sf::Vector2f(12.f * size, 32.f * size));
			_window.rectangle.setOrigin(sf::Vector2f(6.f, 16.f));
			
			_window.draw(_window.rectangle);
		}

		if(_numOfCivilAlive == 10)
			_window.text.setString("Excellent !");
		else if(_numOfCivilAlive > 5)
			_window.text.setString("Very good !");
		else if(_numOfCivilAlive > 0)
			_window.text.setString("good !");
		else
			_window.text.setString("Please man you are so bad as fuck !");

		_window.text.setPosition(_window.viewDefaultPos(sf::Vector2f(960.f,700.f )));
		_window.text.setCharacterSize(50);
		_window.textCenterOrigin();

		_window.draw(_window.text);
	}
}

