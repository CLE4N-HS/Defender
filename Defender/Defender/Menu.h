#pragma once
#include "State.h"
#include "Entity.h"

class Menu : public Entity, public State
{
public:
	Menu();
	~Menu();

	void update(Window& _window, State*& _state);
	void display(Window& _window);

private:

};
