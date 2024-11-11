#include "StateManager.h"
#include "ressourcesManager.h"
#include "Menu.h"
#include "Options.h"
#include "Pause.h"
#include "particleManager.h"
#include "GameOver.h"
#include "soundManager.h"

StateManager::StateManager() : m_state(new Menu), m_isInMenu(true)
{
}

StateManager::~StateManager()
{
}

void StateManager::update(Window& _window, State*& _state)
{
	if (m_timer < 10.f)
		m_timer += _window.getDeltaTime();
	if (!GameOver::isGameOver() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || Gamepad_isButtonPressed(0, gamepadXBOX::START)) && m_timer > 0.5f)
	{
		m_timer = 0.f;
		sound_play("selection");
		if (m_isInMenu)
			Options::toggle();
		else if (!Pause::isOpen() && !Options::isOpen())
			Pause::toggle();
		else if (Pause::isOpen())
			Pause::toggle();
		else
		{
			Options::toggle();
			Pause::toggle();
		}
	}

	if (Pause::isOpen())
		Pause::update(_window);
	else if (Options::isOpen())
		Options::update(_window, m_isInMenu, _state);
	else
		m_state->update(_window, _state);
}

void StateManager::display(Window& _window)
{
	if (Pause::isOpen())
		Pause::display(_window);
	else if (Options::isOpen())
		Options::display(_window, m_isInMenu);
	else
		m_state->display(_window);
}

void StateManager::changeState(State* _state)
{
	delete m_state;
	m_state = _state;

	Menu* menuState = dynamic_cast<Menu*>(_state);
	m_isInMenu = (menuState != nullptr);

	prt_clear();
}
