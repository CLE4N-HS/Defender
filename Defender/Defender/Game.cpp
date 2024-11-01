#include "Game.h"
#include "Lander.h"

Game::Game() : m_viewPos(), m_player()
{
	enemiesList.push_back(new Lander());
}

Game::~Game()
{
}

void Game::update(Window& _window , State*& _state)
{
	m_player.update(_window);
	m_map.update(_window, m_player.getPos());

	for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
		(*it)->update(_window, m_player.getPos());
		
}

void Game::display(Window& _window)
{
	// black background
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	_window.rectangle.setPosition(sf::Vector2f(0.f, 0.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 1080.f));
	_window.rectangle.setOrigin(sf::Vector2f());
	_window.rectangle.setFillColor(sf::Color::Black);
	_window.rectangle.setTexture(nullptr);
	_window.draw(_window.rectangle);
	_window.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
	//

	// main View
	_window.setView(sf::Vector2f(m_player.getPos().x, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	m_player.display(_window, true);
	m_map.display(_window, true, m_player.getPos());

	for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
		(*it)->display(_window,true);
	//
	

	// black background (green for now but TODO just the outline) yeah
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.3f, 0.f, 0.4f, 0.15f), 1.f);

	_window.rectangle.setPosition(sf::Vector2f(0.f, 0.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 1080.f));
	_window.rectangle.setFillColor(sf::Color::Green);
	_window.rectangle.setOrigin(sf::Vector2f());
	_window.rectangle.setTexture(nullptr);
	_window.draw(_window.rectangle);
	_window.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
	//

	// 2nd View
	_window.setView(sf::Vector2f(m_player.getPos().x / 4.f, 540.f), sf::FloatRect(0.3f, 0.f, 0.4f, 0.15f));

	m_player.display(_window, false);
	m_map.display(_window, false, m_player.getPos());
	
	for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
		(*it)->display(_window, false);
	//
}
