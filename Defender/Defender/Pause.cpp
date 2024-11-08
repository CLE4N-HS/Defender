#include "Pause.h"
#include "Options.h"

bool Pause::m_isOpen = false;
int Pause::m_index = 0;

Pause::Pause()
{
}

Pause::~Pause()
{
}

void Pause::toggle()
{
	m_isOpen = !m_isOpen;

	m_index = 0;
}

void Pause::update(Window& _window)
{
	if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Down) ||
		_window.keyboardManager.hasJustPressed(sf::Keyboard::S))
	{
		m_index++;
		if (m_index > 1)
			m_index = 0;
	}
	else if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Up) ||
		_window.keyboardManager.hasJustPressed(sf::Keyboard::Z))
	{
		m_index--;
		if (m_index < 0)
			m_index = 1;
	}

	if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Enter))
	{
		if (m_index == 0)
		{
			Pause::toggle();
			Options::toggle();
		}
		else if (m_index == 1)
		{
			Pause::toggle();
		}
	}
}

void Pause::display(Window& _window)
{
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	_window.text.setCharacterSize(80);
	_window.text.setFillColor(sf::Color::White);

	// PAUSE
	_window.text.setString("PAUSE");
	_window.text.setPosition(960.f, 100.f);
	_window.text.setStyle(sf::Text::Style::Bold);
	_window.textCenterOrigin();

	_window.draw(_window.text);

	_window.text.setCharacterSize(50);

	// OPTIONS
	_window.text.setString("OPTIONS");
	_window.text.setPosition(960.f, 500.f);
	_window.text.setStyle((m_index == 0 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
	_window.textCenterOrigin();

	_window.draw(_window.text);

	// RESUME
	_window.text.setString("RESUME");
	_window.text.setPosition(960.f, 700.f);
	_window.text.setStyle((m_index == 1 ? sf::Text::Style::Underlined : sf::Text::Style::Regular));
	_window.textCenterOrigin();

	_window.draw(_window.text);

	_window.text.setStyle(sf::Text::Style::Regular);
}
