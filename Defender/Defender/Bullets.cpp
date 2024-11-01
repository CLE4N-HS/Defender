#include "Bullets.h"


Bullets::Bullets() : pos(), velocity(), norDirction()
{

}

Bullets::Bullets(sf::Vector2f _pos, sf::Vector2f _norDirection, sf::Vector2f _velocity)
{
	pos = _pos;
	norDirction = _norDirection;
	velocity = _velocity;
}
