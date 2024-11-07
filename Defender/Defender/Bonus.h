#pragma once
#include "Entity.h"
#include "Window.h"

class Bonus : public Entity
{
public:
	Bonus(sf::Vector2f _pos);
	inline ~Bonus() = default;

	virtual void update(Window& _window);
	virtual void display(Window& _window, const bool& mainView);

	inline bool isAlive() const { return m_isAlive; }
	sf::FloatRect getRect() const;

protected:
	bool m_isAlive;
	sf::Vector2f m_size;
	sf::Vector2f m_origin;
	std::string m_anim;

};
