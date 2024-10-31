#include "MouseManager.h"

MouseManager::MouseManager()
{
	for (int button = 0; button < sf::Mouse::ButtonCount; button++)
	{
		m_buttonState[button] = MouseManager::RELEASED;
	}
}

MouseManager::~MouseManager()
{
}

void MouseManager::update(Window& _window)
{
	for (int button = 0; button < sf::Mouse::ButtonCount; button++)
	{
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)button)) {
			m_buttonState[button] = (m_buttonState[button] == MouseManager::JUST_BEEN_PRESSED ? MouseManager::PRESSED : MouseManager::JUST_BEEN_PRESSED);
		}
		else {
			m_buttonState[button] = (m_buttonState[button] == MouseManager::JUST_BEEN_RELEASED ? MouseManager::RELEASED : MouseManager::JUST_BEEN_RELEASED);
		}
	}
}

bool MouseManager::hasJustPressed(sf::Mouse::Button _button)
{
	return (m_buttonState[(int)_button] == MouseManager::JUST_BEEN_PRESSED);
}

bool MouseManager::hasJustReleased(sf::Mouse::Button _button)
{
	return (m_buttonState[(int)_button] == MouseManager::JUST_BEEN_RELEASED);
}
