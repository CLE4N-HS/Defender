#include "Options.h"
#include "Menu.h"
#include "soundManager.h"
#include "musicManager.h"
#include "Pause.h"

bool Options::m_isOpen(false);
int Options::m_songVolume(50);
int Options::m_musicVolume(50);
int Options::m_index(0);

Options::Options()
{
}

Options::~Options()
{
}

void Options::toggle()
{
	m_isOpen = !m_isOpen;
	m_index = 0;
}

void Options::addSongVolume(int _value)
{
	m_songVolume += _value;

	if (m_songVolume < 0)
		m_songVolume = 0;
	else if (m_songVolume > 100)
		m_songVolume = 100;

	sound_setVolume(m_songVolume);
}

void Options::addMusicVolume(int _value)
{
	m_musicVolume += _value;

	if (m_musicVolume < 0)
		m_musicVolume = 0;
	else if (m_musicVolume > 100)
		m_musicVolume = 100;

	music_setVolume(m_musicVolume);
}

void Options::update(Window& _window, const bool& _isInMenu, State*& _state)
{
	if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Down) ||
		_window.keyboardManager.hasJustPressed(sf::Keyboard::S))
	{
		m_index++;
		if (m_index > (_isInMenu ? 2 : 3))
			m_index = 0;
	}
	else if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Up) ||
		_window.keyboardManager.hasJustPressed(sf::Keyboard::Z))
	{
		m_index--;
		if (m_index < 0)
			m_index = (_isInMenu ? 2 : 3);
	}

	// SONG & MUSIC
	if (m_index >= 0 && m_index <= 1)
	{
		int addedVolume(0);

		if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Add) ||
			_window.keyboardManager.hasJustPressed(sf::Keyboard::Right) ||
			_window.keyboardManager.hasJustPressed(sf::Keyboard::D))
			addedVolume = 10;
		else if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Subtract) ||
			_window.keyboardManager.hasJustPressed(sf::Keyboard::Left) ||
			_window.keyboardManager.hasJustPressed(sf::Keyboard::Q))
			addedVolume = -10;


		if (addedVolume != 0)
		{
			if (m_index == 0)
			{
				addSongVolume(addedVolume);
			}
			else if (m_index == 1)
			{
				addMusicVolume(addedVolume);
			}
		}
	}

	// QUIT
	else if (m_index == 2)
	{
		if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Enter))
		{
			if (_isInMenu)
			{
				_window.setIsDone(true);
			}
			else
			{
				_state = new Menu;
				toggle();
			}
		}
	}

	// BACK
	else if (m_index == 3)
	{
		if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Enter))
		{
			Options::toggle();
			Pause::toggle();
		}
	}
}

void Options::display(Window& _window, const bool& _isInMenu)
{
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	_window.text.setCharacterSize(80);
	_window.text.setFillColor(sf::Color::White);

	// OPTIONS
	_window.text.setString("OPTIONS");
	_window.text.setPosition(960.f, 100.f);
	_window.text.setStyle(sf::Text::Style::Bold);
	_window.textCenterOrigin();
	
	_window.draw(_window.text);
	_window.text.setCharacterSize(50);

	// SONG
	_window.text.setString("SONG : " + std::to_string(m_songVolume));
	_window.text.setPosition(960.f, 400.f);
	_window.text.setStyle((m_index == 0 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
	_window.textCenterOrigin();

	_window.draw(_window.text);

	// MUSIC
	_window.text.setString("MUSIC : " + std::to_string(m_musicVolume));
	_window.text.setPosition(960.f, 500.f);
	_window.text.setStyle((m_index == 1 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
	_window.textCenterOrigin();

	_window.draw(_window.text);

	// PLUS
	_window.text.setString("+");
	_window.text.setPosition(1110.f, 364.f);
	_window.text.setStyle((m_index == 0 ? sf::Text::Style::Bold : sf::Text::Style::Regular));
	_window.textCenterStringOrigin();
	_window.draw(_window.text);
	_window.text.setPosition(1110.f, 464.f);
	_window.text.setStyle((m_index == 1 ? sf::Text::Style::Bold : sf::Text::Style::Regular));
	_window.textCenterStringOrigin();
	_window.draw(_window.text);

	// MINUS
	_window.text.setString("-");
	_window.text.setPosition(810.f, 364.f);
	_window.text.setStyle((m_index == 0 ? sf::Text::Style::Bold : sf::Text::Style::Regular));
	_window.textCenterStringOrigin();
	_window.draw(_window.text);
	_window.text.setPosition(810.f, 464.f);
	_window.text.setStyle((m_index == 1 ? sf::Text::Style::Bold : sf::Text::Style::Regular));
	_window.textCenterStringOrigin();
	_window.draw(_window.text);


	// QUIT
	_window.text.setString("QUIT");
	_window.text.setPosition(960.f, 700.f);
	_window.text.setStyle((m_index == 2 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
	_window.textCenterOrigin();

	_window.draw(_window.text);

	if (!_isInMenu)
	{
		// BACK
		_window.text.setString("Back");
		_window.text.setPosition(960.f, 800.f);
		_window.text.setStyle((m_index == 3 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
		_window.textCenterOrigin();

		_window.draw(_window.text);
	}


	_window.text.setStyle(sf::Text::Style::Regular);
}