#include "Menu.h"
#include "controller.h"
#include "Game.h"
#include "textureManager.h"
#include "HighScore.h"

Menu::Menu() : Entity(), m_timer(0.f)
{
}

Menu::~Menu()
{
}

void Menu::update(Window& _window, State*& _state)
{
	if (m_timer < 10.f)
		m_timer += _window.getDeltaTime();

	const bool changeStateInput = (m_timer >= 1.f && (_window.keyboardManager.hasJustPressed(sf::Keyboard::Space) || Gamepad_isButtonPressed(0, gamepadXBOX::A)));

	if (changeStateInput)
	{
		_state = new Game;
	}
}

void Menu::display(Window& _window)
{
	_window.rectangle.setFillColor(sf::Color(255, 255, 255));
	_window.rectangle.setPosition(sf::Vector2f(960.f, 200.f));
	_window.rectangle.setSize(sf::Vector2f(480.f, 168.f));
	_window.rectangle.setOrigin(sf::Vector2f(240.f, 84.f));
	_window.rectangle.setScale(sf::Vector2f(2.f, 2.f));
	_window.rectangle.setTexture(tex_getTexture("menu"), true);

	_window.draw(_window.rectangle);
	_window.rectangle.setScale(sf::Vector2f(1.f, 1.f));

	_window.text.setCharacterSize(30);
	_window.text.setPosition(sf::Vector2f(960.f, 400.f));
	_window.text.setFillColor(sf::Color(255, 255, 255));
	_window.text.setString("SPACE TO PLAY");
	_window.text.setStyle(sf::Text::Style::Italic);
	_window.textCenterOrigin();

	_window.draw(_window.text);
	_window.text.setStyle(sf::Text::Style::Regular);

	HighScore::display(_window);
}
