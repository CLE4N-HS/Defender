#include "KeyboardManager.h"

KeyboardManager::KeyboardManager()
{
	for (int key = 0; key < sf::Keyboard::KeyCount; key++)
	{
		m_keyState[key] = KeyboardManager::RELEASED;
	}
}

KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::update()
{
	for (int key = 0; key < sf::Keyboard::KeyCount; key++)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key)) {
			m_keyState[key] = (m_keyState[key] < KeyboardManager::JUST_BEEN_PRESSED ? KeyboardManager::JUST_BEEN_PRESSED : KeyboardManager::PRESSED);
		}
		else {
			m_keyState[key] = (m_keyState[key] > KeyboardManager::JUST_BEEN_RELEASED ? KeyboardManager::JUST_BEEN_RELEASED: KeyboardManager::RELEASED);
		}
	}
}

bool KeyboardManager::hasJustPressed(sf::Keyboard::Key _key)
{
	return (m_keyState[(int)_key] == KeyboardManager::JUST_BEEN_PRESSED);
}

bool KeyboardManager::hasJustReleased(sf::Keyboard::Key _key)
{
	return (m_keyState[(int)_key] == KeyboardManager::JUST_BEEN_RELEASED);
}