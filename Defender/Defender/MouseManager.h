#pragma once
#include "Window.h"

class MouseManager
{
public:
	typedef enum {
		RELEASED,
		JUST_BEEN_RELEASED,
		JUST_BEEN_PRESSED,
		PRESSED,

		COUNT // <- keep last
	}ButtonState;

	MouseManager();
	~MouseManager();

	void update(Window& _window);
	bool hasJustPressed(sf::Mouse::Button _button);
	bool hasJustReleased(sf::Mouse::Button _button);

private:
	ButtonState m_buttonState[(int)sf::Mouse::ButtonCount];

};
