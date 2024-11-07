#pragma once
#include "SFML/System/Vector2.hpp"

class Entity
{
public:
	Entity();
	Entity(float _posX, float _posY);
	Entity(sf::Vector2f _pos);
	~Entity();

	inline sf::Vector2f getPos() const {return m_pos;}
	inline void setPos(const sf::Vector2f& _pos) { m_pos = _pos; }

protected:
	sf::Vector2f m_pos;

};

