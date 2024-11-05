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


	sf::FloatRect getRect() const;
	sf::Vector2f getPos() const;
	sf::Vector2f getViewCenterPos() const;

	void setDamage(int _damage);
	int getLife() const;

private:
	sf::Vector2f m_pos;
	sf::FloatRect m_colRect;
	sf::Vector2f m_posOffset;
	sf::Vector2f m_saveOffset;
	sf::Vector2f m_previousForward;
	sf::Vector2f m_forward;
	sf::Vector2f m_velocity;

	sf::Vector2f m_size;
	sf::Vector2f m_origin;

	float m_speed;
	float m_movingTime;
	float m_boostTime;
	bool m_wasFacingRight;

	int m_life;
	float m_fireRate;

	bool m_wasMoving;
	bool m_hasReleased;

	float m_facingTime;
	int m_score;

};
