#pragma once
#include "Window.h"
#include "StateManager.h"

// Masterclass
class Master
{
public:
	Master();
	~Master();

	void loop();

private:
	Window m_window;
	StateManager m_stateManager;
	State* m_newState;

};
