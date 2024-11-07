#include "Entity.h"

Entity::Entity() : Entity(sf::Vector2f())
{
}

Entity::Entity(float _posX, float _posY) : Entity(sf::Vector2f(_posX, _posY))
{
}

Entity::Entity(sf::Vector2f _pos) : m_pos(_pos)
{
}

Entity::~Entity()
{
}
