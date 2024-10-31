#pragma once
#include "State.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	void update(Window& _window, State*& _state);
	void display(Window& _window);

	void changeState(State* _state);

private:
	State* m_state;

};
