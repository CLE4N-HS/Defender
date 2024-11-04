#include "Player.h"
#include "textureManager.h"
#include "particleManager.h"

Player::Player() : Player(sf::Vector2f(100.f, 540.f))
{
}

Player::Player(sf::Vector2f _pos) : m_pos(_pos), m_forward(1.f, 0.f), m_speed(1000.f), m_movingTime(0.f), m_wasFacingRight(true), m_hasReleased(true), m_wasMoving(false), m_facingTime(0.f),
	m_boostTime(0.f), m_score(0)
{
	sf::IntRect tmpRect = tex_getAnimRect("all", "playerR");
	m_size = sf::Vector2f(tmpRect.getSize());
	m_origin = m_size * 0.5f;
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


	bool isMoving(false);
	bool isMovingSideway(false);
	bool directionSave = m_wasFacingRight;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (!m_wasMoving)
			m_forward = sf::Vector2f();

		m_forward.y -= dt * 100.f;
		isMoving = true;
		m_wasMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (!m_wasMoving)
			m_forward = sf::Vector2f();

		m_forward.x -= dt * 100.f;
		m_wasFacingRight = false;
		isMoving = true;
		isMovingSideway = true;
		m_wasMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!m_wasMoving)
			m_forward = sf::Vector2f();

		m_forward.y += dt * 100.f;
		isMoving = true;
		m_wasMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isMovingSideway)
	{
		if (!m_wasMoving)
			m_forward = sf::Vector2f();

		m_forward.x += dt * 100.f;
		m_wasFacingRight = true;
		isMoving = true;
		isMovingSideway = true;
		m_wasMoving = true;
	}
	vec2fNormalize(m_forward);

	if (directionSave != m_wasFacingRight)
	{
		m_facingTime = 0.f;
		m_saveOffset = m_posOffset;
		m_boostTime = 0.f;
	}
	else
	{
		m_facingTime += dt * 0.5f;
	}
	m_posOffset = sf::Vector2f(lerp_smooth(m_saveOffset.x, (m_wasFacingRight ? -600.f : 600.f), fminf(m_facingTime, 1.f)), 0.f);


	if (m_facingTime > 1.f)
		m_posOffset.x += (m_wasFacingRight ? 1.f : -1.f) * fminf(m_facingTime - 1.f, 1.f) * 300.f;

	m_posOffset.x += (m_wasFacingRight ? 1.f : -1.f) * m_boostTime * 300.f;

	//if (m_facingTime > 1.f)
	{
		//m_counterSteer.x = (m_posOffset.x < 0.f ? 1.f : -1.f) * fminf(m_movingTime - 1.f, 1.f) * 100.f;
		//m_counterSteer.x = (m_posOffset.x < 0.f ? 1.f : -1.f) * fminf(m_boostTime, 1.f) * 100.f;
		//m_posOffset.x += (m_posOffset.x < 0.f ? 1.f : -1.f) * fminf(m_movingTime - 1.f, 1.f) * 100.f;
	}

	if (isMovingSideway)
	{
		m_boostTime += dt;
		m_boostTime = fminf(m_boostTime, 1.f);
	}
	else
	{
		m_boostTime -= dt;
		m_boostTime = fmaxf(m_boostTime, 0.f);
	}


	if (isMoving)
	{
		m_movingTime += dt;
		m_movingTime = fminf(m_movingTime, 1.f);


		if (m_hasReleased)
		{
			m_velocity = sf::Vector2f();
			m_hasReleased = false;
		}

		m_previousForward = m_forward;
	}
	else
	{
		m_wasMoving = false;
		m_hasReleased = true;

		m_movingTime -= dt;
		m_movingTime = fmaxf(m_movingTime, 0.f);

		m_velocity = lerpVector(sf::Vector2f(), m_velocity, m_movingTime);
		m_forward = lerpVector(sf::Vector2f(), m_previousForward, m_movingTime);
	}

	m_movingTime = fminf(m_movingTime, 1.f);
	m_movingTime = fmaxf(m_movingTime, 0.f);

	m_velocity = m_forward * (m_speed * m_movingTime);


	if (m_velocity.x < 0.001f && m_velocity.x > -0.001f && !isMoving) {
		m_velocity.x = 0.f;
	}
	if (m_velocity.y < 0.001f && m_velocity.y > -0.001f && !isMoving) {
		m_velocity.y = 0.f;
	}



	m_pos += (m_velocity * dt);

	if (m_pos.y < 172.f + m_origin.y)
		m_pos.y = 172.f + m_origin.y;
	if (m_pos.y > 1080.f - m_origin.y)
		m_pos.y = 1080.f - m_origin.y;





	//// NO
	//sf::Vector2f previousForward(m_forward);
	//m_forward = sf::Vector2f(0.f, 0.f);
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

	//// moving time
	//if (m_forward.x == 0.f && m_forward.y == 0.f)
	//{
	//	m_movingTime -= dt * 3.f;
	//	m_movingTime = fmaxf(0.f, m_movingTime);

	//	m_forward = previousForward;
	//}
	//else
	//{
	//	m_movingTime += dt;
	//	m_movingTime = fminf(m_movingTime, 1.f);
	//}
	//m_velocity = m_forward * m_speed;

	//m_speed = fminf(800.f, m_movingTime * 800.f);
	//m_speed = fmaxf(m_speed, 0.f);
	//m_pos += m_velocity * dt;


}

void Player::display(Window& _window, bool mainView)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", (m_wasFacingRight ? "playerR" : "playerL")));
	_window.rectangle.setPosition(_window.viewCorrectPos(m_pos, mainView));
	_window.rectangle.setSize(m_size);
	_window.rectangle.setOrigin(m_origin);
	_window.draw(_window.rectangle);

	if (mainView)
	{
		for (int i = 0; i < 10; i++)
		{
			prt_CreateSquareParticles(m_pos + (sf::Vector2f((!m_wasFacingRight ? m_origin.x + randomFloat(0.f, (m_boostTime * 24.f)) : -m_origin.x - randomFloat(0.f, (m_boostTime * 24.f))), randomFloat(-5.f, 5.f))),
				10, randomColor(), randomColor(), 0.0003f,
				sf::Vector2f(5.f, 5.f), sf::Vector2f(5.f, 5.f), (m_wasFacingRight ? 90.f : 270.f), (m_wasFacingRight ? 90.f : 270.f), 1.f, 0.f,
				0.f, sf::Color(), sf::Color(), false, false, false, nullptr, false, false, wichParticles::FIRE);
		}
	}

}

sf::Vector2f Player::getPos() const
{
	return m_pos;
}

sf::Vector2f Player::getViewCenterPos() const
{
	return (m_pos - m_posOffset);
}
