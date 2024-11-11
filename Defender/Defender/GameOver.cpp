#include "GameOver.h"
#include "controller.h"
#include <optional>
#include "HighScore.h"
#include "Game.h"
#include "Menu.h"
#include "soundManager.h"
#include "musicManager.h"

bool GameOver::m_isGameOver = false;

int GameOver::m_index = 0;

bool  GameOver::m_isSavingScore = false;
int  GameOver::m_scoreIndex = 0;
float  GameOver::m_scoreTimer = 0.f;
std::string GameOver::m_name = "";
float  GameOver::m_nameTimer = 0.f;
bool  GameOver::m_nameHighlight = false;

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

void GameOver::update(Window& _window, State*& _state, Player& _player)
{
	float dt = _window.getDeltaTime();

	sf::Vector2f stickPos = Gamepad_getStickPos(0, STICKL);

	// up down enter
	int direction(0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || stickPos.y < -30.f)
		direction = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || stickPos.y > 30.f)
		direction = 2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || Gamepad_isButtonPressed(0, gamepadXBOX::A))
		direction = 3;

	if (m_scoreTimer < 10.f)
		m_scoreTimer += dt;

	if (m_isSavingScore)
	{

		m_nameTimer += dt;
		if (m_nameTimer > 0.2f)
		{
			m_nameTimer = 0.f;
			m_nameHighlight = !m_nameHighlight;
		}

		if (direction != 0 && m_scoreTimer > 0.2f)
		{
			m_scoreTimer = 0.f;

			if (direction == 1)
			{
				m_name[m_scoreIndex] -= 1;
				if (m_name[m_scoreIndex] < 'A')
					m_name[m_scoreIndex] = 'Z';
				sound_play("selection");
			}
			else if (direction == 2)
			{
				m_name[m_scoreIndex] += 1;
				if (m_name[m_scoreIndex] > 'Z')
					m_name[m_scoreIndex] = 'A';
				sound_play("selection");
			}
			else if (direction == 3)
			{
				m_scoreIndex++;
				if (m_scoreIndex > 2)
				{
					HighScore::addScore(_player.getScore(), m_name);
					m_isSavingScore = false;
					m_index = 0;
					m_scoreTimer = 0.f;
				}
				else
					m_name.push_back('A');

				sound_play("press");
			}
		}
	}
	else if (m_isGameOver)
	{
		if (m_scoreTimer > 0.3f)
		{
			if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Z) || _window.keyboardManager.hasJustPressed(sf::Keyboard::Up) || stickPos.y < -30.f)
			{
				m_scoreTimer = 0.f;
				m_index--;
				if (m_index < 0)
					m_index = 1;
				sound_play("selection");
			}
			else if (_window.keyboardManager.hasJustPressed(sf::Keyboard::S) || _window.keyboardManager.hasJustPressed(sf::Keyboard::Down) || stickPos.y > 30.f)
			{
				m_scoreTimer = 0.f;
				m_index++;
				if (m_index > 1)
					m_index = 0;
				sound_play("selection");
			}
			else if (direction == 3)
			{
				if (m_index == 0)
				{
					sound_play("press");
					m_isGameOver = false;
					// RESTART A GAME
					_state = new Game;
				}
				else if (m_index == 1)
				{
					sound_play("press");
					m_isGameOver = false;
					music_stop("game");
					music_stop("gameOver");
					_state = new Menu;
				}
			}
		}

	}
}

void GameOver::display(Window& _window)
{
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	if (m_isSavingScore)
	{
		_window.text.setCharacterSize(60);
		_window.text.setFillColor(sf::Color(192, 25, 167));
		_window.text.setStyle(sf::Text::Style::Regular);


		_window.text.setString("PLAYER ONE");
		_window.text.setPosition(960.f, 100.f);
		_window.textCenterOrigin();
		_window.draw(_window.text);

		_window.text.setString("YOU HAVE QUALIFIED FOR");
		_window.text.setPosition(960.f, 300.f);
		_window.textCenterOrigin();
		_window.draw(_window.text);

		_window.text.setString("THE DEFENDER HALL OF FAME");
		_window.text.setPosition(960.f, 360.f);
		_window.textCenterOrigin();
		_window.draw(_window.text);

		_window.text.setString("SELECT INITALS WITH UP DOWN STICK");
		_window.text.setPosition(960.f, 500.f);
		_window.textCenterOrigin();
		_window.draw(_window.text);

		_window.text.setString("PRESS FIRE TO ENTER INITIAL");
		_window.text.setPosition(960.f, 650.f);
		_window.textCenterOrigin();
		_window.draw(_window.text);

		for (int i = 0; i < 3; i++)
		{
			std::string letter;

			if (i < m_name.size())
				letter = m_name[i];
			else
				letter = "";

			sf::Vector2f pos(920.f + static_cast<float>(i) * 40.f, 730.f);

			_window.text.setString(letter);
			_window.text.setPosition(pos);
			_window.text.setStyle(sf::Text::Style::Regular);
			_window.textCenterStringOrigin();
			_window.draw(_window.text);


			if (i != m_scoreIndex || !m_nameHighlight)
			{
				_window.text.setString("  ");
				_window.text.setPosition(pos + sf::Vector2f(3.f, +20.f));
				_window.text.setStyle(sf::Text::Style::Underlined);
				_window.textCenterStringOrigin();
				_window.draw(_window.text);
			}
		}
	}
	else if (m_isGameOver)
	{
		_window.text.setCharacterSize(80);
		_window.text.setFillColor(sf::Color::White);

		// GAME OVER
		_window.text.setString("GAME OVER");
		_window.text.setPosition(960.f, 100.f);
		_window.text.setStyle(sf::Text::Style::Bold);
		_window.textCenterOrigin();

		_window.draw(_window.text);

		_window.text.setCharacterSize(50);

		// PLAY AGAIN
		_window.text.setString("PLAY AGAIN");
		_window.text.setPosition(960.f, 500.f);
		_window.text.setStyle((m_index == 0 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
		_window.textCenterOrigin();

		_window.draw(_window.text);

		// QUIT
		_window.text.setString("QUIT");
		_window.text.setPosition(960.f, 700.f);
		_window.text.setStyle((m_index == 1 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
		_window.textCenterOrigin();

		_window.draw(_window.text);
	}

	_window.text.setStyle(sf::Text::Style::Regular);
}

void GameOver::setup(const int& _score)
{
	m_isGameOver = !m_isGameOver;
	m_index = 0;
	m_isSavingScore = HighScore::isScoreHighEnough(_score);
	m_scoreIndex = 0;
	m_scoreTimer = 0.f;
	m_name = "A";
	m_nameTimer = 0.f;
	m_nameHighlight = false;
	music_stop("game");
	music_play("gameOver");
	music_setLoop("gameOver");

}
