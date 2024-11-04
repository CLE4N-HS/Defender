#include "Game.h"
#include "particleManager.h"

Game::Game() : m_viewPos(), m_player()
{
}

Game::~Game()
{
}

void Game::update(Window& _window , State*& _state)
{
	m_player.update(_window);
	m_map.update(_window, m_player.getPos());

	prt_UpdateParticles(_window.getDeltaTime());
}

void Game::display(Window& _window)
{
	// black background
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	_window.rectangle.setPosition(sf::Vector2f(0.f, 0.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 1080.f));
	_window.rectangle.setFillColor(sf::Color::Black);
	_window.rectangle.setTexture(nullptr);
	_window.draw(_window.rectangle);

	// hud TODO
	_window.rectangle.setPosition(sf::Vector2f(576.f - 10.f, 0.f - 10.f));
	_window.rectangle.setSize(sf::Vector2f(768.f + 20.f, 162.f + 20.f));
	_window.rectangle.setFillColor(sf::Color::Green);
	_window.draw(_window.rectangle);
	//

	_window.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
	//

	// main View
	_window.setView(sf::Vector2f(m_player.getViewCenterPos().x, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	m_map.display(_window, true, m_player.getViewCenterPos());
	m_player.display(_window, true);

	prt_DisplayParticlesBehind(_window, _window.getDeltaTime());

	//
	

	// black background (green for now but TODO just the outline)
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.3f, 0.f, 0.4f, 0.15f), 1.f);

	_window.rectangle.setPosition(sf::Vector2f(0.f, 0.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 1080.f));
	_window.rectangle.setFillColor(sf::Color::Black);
	_window.rectangle.setTexture(nullptr);
	_window.draw(_window.rectangle);
	_window.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
	_window.rectangle.setOutlineThickness(0.f);
	//

	// 2nd View
	_window.setView(sf::Vector2f(m_player.getViewCenterPos().x / 4.f, 540.f), sf::FloatRect(0.3f, 0.f, 0.4f, 0.15f));

	m_player.display(_window, false);
	m_map.display(_window, false, m_player.getViewCenterPos());
	//
}
