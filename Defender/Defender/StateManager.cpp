#include "StateManager.h"
#include "ressourcesManager.h"
#include "Game.h"

StateManager::StateManager() : m_state(new Game)
{
	res_load(RES_ALL);
}

StateManager::~StateManager()
{
}

void StateManager::update(Window& _window, State*& _state)
{
	m_state->update(_window, _state);
}

void StateManager::display(Window& _window)
{
	m_state->display(_window);
}

void StateManager::changeState(State* _state)
{
	delete m_state;
	m_state = _state;
}
