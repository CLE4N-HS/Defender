#include "Multiplication.h"

int Multiplication::m_multiplier(1);
Multiplication multiplication;

Multiplication::Multiplication()
{
	m_multiplier = 1;
}

Multiplication::~Multiplication()
{
}

void Multiplication::displayMultiplication(Window& _window)
{

	_window.text.setPosition(sf::Vector2f(1640.f, 81.f));
	_window.text.setCharacterSize(40 + 10 * (m_multiplier > 4 ? 4 : m_multiplier));
	_window.text.setString("Multiplier x" + std::to_string(m_multiplier));
	_window.text.setStyle(sf::Text::Style::Regular);
	_window.textCenterOrigin();

	float iTime = _window.getItime();

	float r = cosf(sinf(iTime) * 10.f) * 0.5f + 0.5f;
	float g = cosf(sinf(iTime) * 20.f) * 0.5f + 0.5f;
	float b = cosf(sinf(iTime) * 30.f) * 0.5f + 0.5f;

	_window.text.setFillColor(sf::Color(static_cast<sf::Uint8>(r * 255.f), static_cast<sf::Uint8>(g * 255.f), static_cast<sf::Uint8>(b * 255.f)));


	_window.draw(_window.text);
}
