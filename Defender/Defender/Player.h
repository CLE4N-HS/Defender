#pragma once
#include "Window.h"

class Player
{
public:
	Player();
	Player(sf::Vector2f _pos);
	~Player();

	void update(Window& _window);
	void display(Window& _window, bool mainView);

	sf::Vector2f getPos();
	sf::Vector2f getCenter();

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_posOffset;
	sf::Vector2f m_saveOffset;
	sf::Vector2f m_previousForward;
	sf::Vector2f m_forward;
	sf::Vector2f m_velocity;
	float m_speed;
	float m_movingTime;
	bool m_wasFacingRight;
	bool m_wasMoving;
	bool m_hasReleased;

	float m_facingTime;

};
