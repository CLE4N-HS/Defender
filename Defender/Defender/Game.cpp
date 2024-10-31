#include "Game.h"

Game::Game() : m_viewPos()
{
	//enemiesList.push_back(new Lander());
}

Game::~Game()
{
}

void Game::update(Window& _window , State*& _state)
{
}

void Game::display(Window& _window)
{
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f), 1.f);

	_window.rectangle.setPosition(sf::Vector2f(0.f, 0.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 1080.f));
	_window.rectangle.setFillColor(sf::Color::Black);
	_window.draw(_window.rectangle);

	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.3f, 0.f, 0.4f, 0.15f), 1.f);

	_window.rectangle.setPosition(sf::Vector2f(0.f, 0.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 1080.f));
	_window.rectangle.setFillColor(sf::Color::Green);
	_window.draw(_window.rectangle);
}
