#pragma once
#include "State.h"

class Game : public State
{
public:
	Game();
	virtual ~Game();
	virtual void update(Window& _window, State*& _state);
	virtual void display(Window& _window);

private:

};