#include "Hud.h"
#include "textureManager.h"

Hud::Hud()
{
}

Hud::~Hud()
{
}

void Hud::display(Window& _window, Player& _player)
{
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	_window.rectangle.setOrigin(sf::Vector2f());
	_window.rectangle.setTexture(nullptr);

	_window.rectangle.setPosition(sf::Vector2f());
	_window.rectangle.setSize(sf::Vector2f(1920.f, 172.f));
	_window.rectangle.setFillColor(sf::Color::Black);
	_window.draw(_window.rectangle);

	_window.rectangle.setPosition(sf::Vector2f(576.f - 10.f, 0.f - 10.f));
	_window.rectangle.setSize(sf::Vector2f(768.f + 20.f, 162.f + 20.f));
	_window.rectangle.setFillColor(sf::Color::Green);
	_window.draw(_window.rectangle);

	_window.rectangle.setPosition(sf::Vector2f(0.f, 162.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 10.f));
	_window.draw(_window.rectangle);

	_window.rectangle.setFillColor(sf::Color(255, 255, 255));

	
	const int playerLife = _player.getLife() - 1;

	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", "playerR"));
	_window.rectangle.setSize(sf::Vector2f(60.f, 24.f));

	sf::Vector2f lifePos(50.f, 50.f);
	for (int i = 0; i < playerLife; i++)
	{
		_window.rectangle.setPosition(lifePos);
		_window.draw(_window.rectangle);

		lifePos.x += 80.f;
	}
	

	const int playerBomb = _player.getBomb();

	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", "bomb"));
	_window.rectangle.setSize(sf::Vector2f(24.f, 12.f));

	sf::Vector2f bombPos(500.f, 100.f);
	for (int i = 0; i < playerBomb; i++)
	{
		_window.rectangle.setPosition(bombPos);
		_window.draw(_window.rectangle);

		bombPos.y += 20.f;
	}


	_window.text.setString(std::to_string(_player.getScore()));
	_window.text.setOrigin(sf::Vector2f());
	_window.text.setPosition(sf::Vector2f(100.f, 80.f));
	_window.text.setCharacterSize(50);

	float iTime = _window.getItime();

	float r = cosf(sinf(iTime) * 10.f) * 0.5f + 0.5f;
	float g = cosf(sinf(iTime) * 20.f) * 0.5f + 0.5f;
	float b = cosf(sinf(iTime) * 30.f) * 0.5f + 0.5f;

	_window.text.setFillColor(sf::Color(static_cast<sf::Uint8>(r * 255.f), static_cast<sf::Uint8>(g * 255.f), static_cast<sf::Uint8>(b * 255.f)));


	_window.draw(_window.text);
	

	_window.rectangle.setTexture(nullptr);
}
