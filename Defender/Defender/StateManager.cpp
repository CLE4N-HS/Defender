#include "StateManager.h"
#include "ressourcesManager.h"
#include "Menu.h"
#include "Options.h"

StateManager::StateManager() : m_state(new Menu), m_isInMenu(true)
{
}

StateManager::~StateManager()
{
}

void StateManager::update(Window& _window, State*& _state)
{
	if (_window.keyboardManager.hasJustPressed(sf::Keyboard::Escape))
		Options::toggle();

	if (Options::isOpen())
		Options::update(_window, m_isInMenu, _state);
	else
		m_state->update(_window, _state);
}

void StateManager::display(Window& _window)
{
	if (Options::isOpen())
		Options::display(_window);
	else
		m_state->display(_window);
}

void StateManager::changeState(State* _state)
{
	delete m_state;
	m_state = _state;

	Menu* menuState = dynamic_cast<Menu*>(_state);
	m_isInMenu = (menuState != nullptr);
}
