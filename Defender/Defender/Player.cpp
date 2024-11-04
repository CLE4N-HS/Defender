#include "Player.h"
#include "textureManager.h"
#include "playerBullets.h"

Player::Player() : Player(sf::Vector2f(100.f, 540.f))
{
}

Player::Player(sf::Vector2f _pos) : m_pos(_pos),m_size(), m_forward(1.f, 0.f), m_speed(0.f), m_movingTime(0.f), m_wasFacingRight(true), m_colRect()
{
	m_life = 100.f;
	m_fireRate = 0.2f;
}

Player::~Player()
{
}

void Player::update(Window& _window, std::list<Bullets*>& _bulletsList)
{
	float dt = _window.getDeltaTime();
	m_fireRate -= dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_fireRate < 0.0f )
	{
		m_fireRate = 0.2f;
		_bulletsList.push_back(new playerBullets(m_pos,m_wasFacingRight == 1 ? sf::Vector2f(1.f,0.f) : sf::Vector2f(-1.f, 0.f),sf::Vector2f(2000.f,2000.f)));
	}


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

	m_speed = fminf(800.f, m_movingTime * 800.f);
	m_speed = fmaxf(m_speed, 0.f);
	m_pos += m_velocity * dt;
}

void Player::display(Window& _window, bool mainView)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", (m_wasFacingRight ? "playerR" : "playerL")));
	//_window.rectangle.setPosition(mainView ? m_pos : sf::Vector2f(m_pos.x / 4.f, m_pos.y)); don't use this, just an example
	_window.rectangle.setPosition(_window.viewCorrectPos(m_pos, mainView));
	_window.rectangle.setSize(sf::Vector2f(60.f, 24.f));
	_window.rectangle.setOrigin(sf::Vector2f(30.f, 12.f));
	m_size = _window.rectangle.getSize();
	m_colRect = sf::FloatRect(m_pos - _window.rectangle.getOrigin(), m_size);
	_window.draw(_window.rectangle);

}

sf::Vector2f Player::getPos()
{
	return m_pos;
}

sf::FloatRect Player::getRect() const
{
	return m_colRect;
}

void Player::setDamage(int _damage)
{
	m_life -= _damage;
}
