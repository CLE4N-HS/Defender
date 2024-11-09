#include "Pause.h"
#include "Options.h"

bool Pause::m_isOpen = false;
int Pause::m_index = 0;
float Pause::m_timer(0.f);

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
	m_timer = 0.f;
}

void Pause::update(Window& _window)
{
	if (m_timer < 10.f)
		m_timer += _window.getDeltaTime();

	if (m_timer < 0.2f)
		return;

	sf::Vector2f stickPos = Gamepad_getStickPos(0, STICKL);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		stickPos.y > +30.f)
	{
		m_timer = 0.f;
		m_index++;
		if (m_index > 1)
			m_index = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
		stickPos.y < -30.f)
	{
		m_timer = 0.f;
		m_index--;
		if (m_index < 0)
			m_index = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
		Gamepad_isButtonPressed(0, A))
	{
		if (m_index == 0)
		{
			m_timer = 0.f;
			Pause::toggle();
			Options::toggle();
		}
		else if (m_index == 1)
		{
			m_timer = 0.f;
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
