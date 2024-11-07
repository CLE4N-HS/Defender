#include "Bonus.h"
#include "textureManager.h"

Bonus::Bonus(sf::Vector2f _pos) : Entity(_pos), m_isAlive(true), m_size(72.f, 72.f), m_origin(36.f, 36.f), m_anim()
{
}

void Bonus::update(Window& _window)
{
	float dt = _window.getDeltaTime();

	m_pos.y += 100 * dt;


	if (m_pos.y + m_origin.y > 1080.f)
		m_isAlive = false;
}

void Bonus::display(Window& _window, const bool& mainView)
{
	_window.rectangle.setPosition(_window.viewCorrectPos(m_pos, mainView));
	_window.rectangle.setSize(m_size);
	_window.rectangle.setOrigin(m_origin);
	_window.rectangle.setScale(_window.viewCorrectScale(sf::Vector2f(1.f, 1.f), mainView));
	_window.rectangle.setTexture(tex_getTexture("bonus"));
	_window.rectangle.setTextureRect(tex_getAnimRect("bonus", m_anim.c_str()));
	
	_window.draw(_window.rectangle);
}

sf::FloatRect Bonus::getRect() const
{
	return (sf::FloatRect(m_pos - m_origin, m_size));
}
