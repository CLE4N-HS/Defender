#include "Game.h"
#include "Lander.h"
#include "particleManager.h"
#include "Menu.h"
#include "HighScore.h"

Game::Game() : m_viewPos(), m_player()
{
	for (int i = 0; i < 10; i++)
	{
		civilianList.push_back(new civilians());
	}
}

Game::~Game()
{
}

void Game::update(Window& _window , State*& _state)
{
	m_wave.update(_window, enemiesList, m_player.getPos());

	if (!m_wave.isScreenWave())
	{
		_window.setView(sf::Vector2f(m_player.getViewCenterPos().x, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

		if (m_player.getLife() > 0)
			m_player.update(_window, bulletsList);

		m_map.update(_window, m_player.getPos());

		for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
			(*it)->update(_window, m_player, bulletsList);

		for (std::list<Bullets*>::iterator it = bulletsList.begin(); it != bulletsList.end(); it++)
			(*it)->update(_window, particuleList);

		for (std::list<civilians*>::iterator it = civilianList.begin(); it != civilianList.end(); it++)
			(*it)->update(_window);

		for (std::list<Particule*>::iterator it = particuleList.begin(); it != particuleList.end();)
		{
			if ((*it)->getTimerValue() > 0)
			{
				(*it)->update(_window);
				it++;
			}
			else
				it = particuleList.erase(it);
		}

		colManager.update(bulletsList, m_player, enemiesList);
		detectionManager.update(enemiesList, civilianList);
		prt_UpdateParticles(_window.getDeltaTime());
	}		
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

	if (!m_wave.isScreenWave())
	{
		m_map.display(_window, true, m_player.getViewCenterPos());

		if (m_player.getLife() > 0)
			m_player.display(_window, true);

		for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
			(*it)->display(_window, true);

		for (std::list<Bullets*>::iterator it = bulletsList.begin(); it != bulletsList.end(); it++)
			(*it)->display(_window);

		for (std::list<Particule*>::iterator it = particuleList.begin(); it != particuleList.end(); it++)
			(*it)->display(_window);

		for (std::list<civilians*>::iterator it = civilianList.begin(); it != civilianList.end(); it++)
			(*it)->display(_window,true);

		prt_DisplayParticlesBehind(_window, _window.getDeltaTime());
	}
	else
		m_wave.display(_window);


	//
	

	// black background (green for now but TODO just the outline) yeah
	_window.setView(sf::Vector2f(960.f, 540.f), sf::FloatRect(0.3f, 0.f, 0.4f, 0.15f), 1.f);

	_window.rectangle.setPosition(sf::Vector2f(0.f, 0.f));
	_window.rectangle.setSize(sf::Vector2f(1920.f, 1080.f));
	_window.rectangle.setOrigin(sf::Vector2f());
	_window.rectangle.setFillColor(sf::Color::Black);
	_window.rectangle.setTexture(nullptr);
	_window.draw(_window.rectangle);
	_window.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
	//

	// 2nd View
	_window.setView(sf::Vector2f(m_player.getViewCenterPos().x *0.25f, 540.f), sf::FloatRect(0.3f, 0.f, 0.4f, 0.15f));

	m_player.display(_window, false);
	
	for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
		(*it)->display(_window, false);

	for (std::list<civilians*>::iterator it = civilianList.begin(); it != civilianList.end(); it++)
		(*it)->display(_window, false);

	m_map.display(_window, false, m_player.getViewCenterPos());

	//
}
