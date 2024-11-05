#pragma once
#include "tools.h"

class KeyboardManager
{
public:
	typedef enum {
		RELEASED,
		JUST_BEEN_RELEASED,
		JUST_BEEN_PRESSED,
		PRESSED,

		COUNT // <- keep last
	}KeyState;

	KeyboardManager();
	~KeyboardManager();

	void update();
	bool hasJustPressed(sf::Keyboard::Key _key);
	bool hasJustReleased(sf::Keyboard::Key _key);

private:
	KeyState m_keyState[(int)sf::Keyboard::KeyCount];

};

