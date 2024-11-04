#pragma once
#include "Window.h"
#include "Bullets.h"

class Player
{
public:
	Player();
	Player(sf::Vector2f _pos);
	~Player();

	void update(Window& _window, std::list<Bullets*>& _bulletsList);
	void display(Window& _window, bool mainView);

	sf::Vector2f getPos();
	sf::FloatRect getRect() const;

	void setDamage(int _damage);
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Vector2f m_forward;
	sf::Vector2f m_velocity;
	sf::FloatRect m_colRect;
	float m_speed;
	float m_movingTime;
	bool m_wasFacingRight;
	int m_life;
	float m_fireRate;
};
