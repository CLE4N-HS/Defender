#include "Bullets.h"


Bullets::Bullets() : pos(), velocity(), norDirction()
{

}

Bullets::Bullets(sf::Vector2f _pos, sf::Vector2f _viewPos, sf::Vector2f _norDirection, sf::Vector2f _velocity)
{
	pos = _pos;
	viewPos = _viewPos;
	norDirction = _norDirection;
	velocity = _velocity;
}
