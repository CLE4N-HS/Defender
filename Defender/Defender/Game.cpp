#include "Game.h"
#include "Lander.h"
#include "particleManager.h"
#include "Menu.h"
#include "HighScore.h"
#include "BonusManager.h"

Game::Game() : m_viewPos(), m_player(), m_detectionPlayerBonus()
{
	enemiesList.push_back(new Lander());
	enemiesList.push_back(new Lander());
	enemiesList.push_back(new Lander());
	enemiesList.push_back(new Lander());
	enemiesList.push_back(new Lander());
	enemiesList.push_back(new Lander());
	enemiesList.push_back(new Lander());
}

Game::~Game()
{
}

void Game::update(Window& _window , State*& _state)
{
	_window.setView(sf::Vector2f(m_player.getViewCenterPos().x, 540.f), sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	m_player.update(_window, bulletsList);
	m_map.update(_window, m_player.getPos());

	for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
		(*it)->update(_window, m_player.getPos(), bulletsList);

	for (std::list<Bullets*>::iterator it = bulletsList.begin(); it != bulletsList.end(); it++)
		(*it)->update(_window, particuleList);

	BonusManager::update(_window);

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
		
	prt_UpdateParticles(_window.getDeltaTime());


	m_detectionPlayerBonus.detectCollision(m_player);


	if (_window.keyboardManager.hasJustPressed(sf::Keyboard::M))
	{
		HighScore::save();
		_state = new Menu;
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

	m_map.display(_window, true, m_player.getViewCenterPos());
	m_player.display(_window, true);

	for (std::list<Enemies*>::iterator it = enemiesList.begin(); it != enemiesList.end(); it++)
		(*it)->display(_window,true);

	for (std::list<Bullets*>::iterator it = bulletsList.begin(); it != bulletsList.end(); it++)
		(*it)->display(_window);

	BonusManager::display(_window, true);

	for (std::list<Particule*>::iterator it = particuleList.begin(); it != particuleList.end(); it++)
		(*it)->display(_window);

	prt_DisplayParticlesBehind(_window, _window.getDeltaTime());


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

	BonusManager::display(_window, false);

	m_map.display(_window, false, m_player.getViewCenterPos());

	//
}
