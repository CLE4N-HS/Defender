#include "Player.h"
#include "textureManager.h"

Player::Player() : Player(sf::Vector2f(100.f, 100.f))
{
}

Player::Player(sf::Vector2f _pos) : m_pos(_pos), m_forward(1.f, 0.f), m_speed(0.f), m_movingTime(0.f), m_wasFacingRight(true)
{
}

Player::~Player()
{
}

void Player::update(Window& _window)
{
	float dt = _window.getDeltaTime();

	//sf::Vector2f previousForward(m_forward);
	////m_forward = sf::Vector2f(0.f, 0.f);
	//bool isMoving(false);
	//// keyboard Movement
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	//{
	//	m_forward.y -= 1.f;
	//	isMoving = true;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	//{
	//	m_forward.x -= 1.f;
	//	m_wasFacingRight = false;
	//	isMoving = true;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	m_forward.y += 1.f;
	//	isMoving = true;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	m_forward.x += 1.f;
	//	m_wasFacingRight = true;
	//	isMoving = true;
	//}
	//vec2fNormalize(m_forward);
	//
	//// moving time
	//if (isMoving)
	//{
	//	m_movingTime -= dt;
	//	m_movingTime = fmaxf(0.f, m_movingTime);
	//}
	//else
	//{
	//	m_movingTime += dt;
	//	m_movingTime = fminf(m_movingTime, 1.f);
	//}
	//
	//
	//
	//m_speed = 500.f;
	//m_velocity = m_forward * m_speed * dt;
	//
	////m_speed = fminf(500.f, m_movingTime * 500.f);
	////m_speed = fmaxf(m_speed, 0.f);
	//m_pos += m_velocity * dt;











	sf::Vector2f previousForward(m_forward);
	m_forward = sf::Vector2f(0.f, 0.f);
	bool isMoving(false);
	// keyboard Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_forward.y -= 1.f;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_forward.x -= 1.f;
		m_wasFacingRight = false;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_forward.y += 1.f;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_forward.x += 1.f;
		m_wasFacingRight = true;
		isMoving = true;
	}
	vec2fNormalize(m_forward);

	// moving time
	if (m_forward.x == 0.f && m_forward.y == 0.f)
	{
		m_movingTime -= dt * 3.f;
		m_movingTime = fmaxf(0.f, m_movingTime);

		m_forward = previousForward;
	}
	else
	{
		m_movingTime += dt;
		m_movingTime = fminf(m_movingTime, 1.f);
	}
	m_velocity = m_forward * m_speed;

	m_speed = fminf(500.f, m_movingTime * 500.f);
	m_speed = fmaxf(m_speed, 0.f);
	m_pos += m_velocity * dt;

}

void Player::display(Window& _window)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", (m_wasFacingRight ? "playerR" : "playerL")));
	_window.rectangle.setPosition(m_pos);
	_window.rectangle.setSize(sf::Vector2f(60.f, 24.f));
	_window.rectangle.setOrigin(sf::Vector2f(30.f, 12.f));
	_window.draw(_window.rectangle);
}
