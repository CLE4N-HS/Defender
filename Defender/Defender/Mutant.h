#pragma once
#include "Enemies.h"

class mutant : public Enemies
{
public:
	mutant();

	virtual void update(Window& _window);
	virtual void display(Window& _window);


private:


};

