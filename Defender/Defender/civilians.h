#pragma once
#include "Window.h"

class civilians
{

public:
	civilians();

	void update();
	void display();


private:
	sf::Vector2f m_pos;
	
	bool isGrabbed;

};

