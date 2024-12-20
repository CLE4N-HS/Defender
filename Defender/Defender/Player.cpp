#include "Player.h"
#include "textureManager.h"
#include "playerBullets.h"
#include "particleManager.h"
#include "soundManager.h"

Player::Player() : Player(sf::Vector2f(100.f, 540.f))
{
}

Player::Player(sf::Vector2f _pos) : m_pos(_pos), m_forward(1.f, 0.f), m_speed(1000.f), m_movingTime(0.f), m_wasFacingRight(true), m_hasReleased(true), m_wasMoving(false), m_facingTime(0.f),
	m_boostTime(0.f), m_score(0), m_colRect(), m_invulnerability(1.f), m_deadTimer(3.f)
{
	sf::IntRect tmpRect = tex_getAnimRect("all", "playerR");
	m_size = sf::Vector2f(tmpRect.getSize());
	m_origin = m_size * 0.5f;
	m_life = 3;
	m_maxFireRate = 0.5f;
	m_fireRate = m_maxFireRate;
	m_bomb = 3;

}

Player::~Player()
{
}

void Player::update(Window& _window, std::list<Bullets*>& _bulletsList)
{
	float dt = _window.getDeltaTime();

	if (m_deadTimer > -10.f && m_life <= 0)
		m_deadTimer -= dt;

	if (m_life <= 0)
		return;

	if (m_fireRate > -10.f)
		m_fireRate -= dt;
	if (m_invulnerability > -10.f)
		m_invulnerability -= dt;
	

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || Gamepad_isButtonPressed(0, gamepadXBOX::X) || Gamepad_getTriggerPos(0, false) > 0.1f) && m_fireRate < 0.0f)
	{
		m_fireRate = m_maxFireRate;
		_bulletsList.push_back(new playerBullets(m_pos, _window.viewCurrentPos(m_pos), m_wasFacingRight == 1 ? sf::Vector2f(1.f,0.f) : sf::Vector2f(-1.f, 0.f),sf::Vector2f(2000.f,2000.f)));
		sound_play("shot");
	}

	bool isMoving(false);
	bool isMovingSideway(false);
	bool directionSave = m_wasFacingRight;

	sf::Vector2f leftStickPos = Gamepad_getStickPos(0, STICKL);

	bool up    = ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || leftStickPos.y < -10.f);
	bool down  = ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) || leftStickPos.y > +10.f);
	bool left  = ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || leftStickPos.x < -10.f);
	bool right = ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) || leftStickPos.x > +10.f);
	bool cheatcode = (up && down && left && right); // little easter egg

	if (up)
	{
		if (!m_wasMoving)
			m_forward = sf::Vector2f();

		m_forward.y -= dt * 100.f;
		isMoving = true;
		m_wasMoving = true;
	}
	if (left)
	{
		if (!m_wasMoving)
			m_forward = sf::Vector2f();

		m_forward.x -= dt * 100.f;
		m_wasFacingRight = false;
		isMoving = true;
		isMovingSideway = true;
		m_wasMoving = true;
	}
	if (down)
	{
		if (!m_wasMoving)
			m_forward = sf::Vector2f();

		m_forward.y += dt * 100.f;
		isMoving = true;
		m_wasMoving = true;
	}
	if (right)
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


}

void Player::display(Window& _window, bool mainView)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	_window.rectangle.setTextureRect(tex_getAnimRect("all", (m_wasFacingRight ? "playerR" : "playerL")));
	_window.rectangle.setPosition(_window.viewCorrectPos(m_pos, mainView));
	_window.rectangle.setSize(m_size);
	_window.rectangle.setOrigin(m_origin);
	m_colRect = sf::FloatRect(m_pos - _window.rectangle.getOrigin(), m_size);
	
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

sf::FloatRect Player::getRect() const
{
	return m_colRect;
}

void Player::setDamage(int _damage)
{
	if (m_invulnerability > 0.f)
		return;

	m_life -= _damage;
	if (m_life > 0)
	{
		for (int i = 0; i < 10; i++)
		{
			prt_CreateSquareParticles(m_pos, 1, sf::Color::White, sf::Color(255, 255, 255, 0), 3.f, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.f, 10.f), 0, 360, static_cast<float>(i + 10) * 100.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
		}
		m_invulnerability = 1.f;
		sound_play("hit");
	}
	else
	{
		for (int i = 0; i < 100; i++)
		{
			prt_CreateSquareParticles(m_pos, 1, sf::Color::White, sf::Color::White, m_deadTimer, sf::Vector2f(10.0f, 10.0f), sf::Vector2f(10.f, 10.f), 0, 360, static_cast<float>(i + 10) * 10.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
		}
		sound_play("death");
	}
}

void Player::useBomb(int _nbBomb)
{
	m_bomb -= _nbBomb;

	if (m_bomb < 0)
		m_bomb = 0;
	// TODO song
}

sf::Vector2f Player::getViewCenterPos() const
{
	return (m_pos - m_posOffset);
}

void Player::decreaseFirerate(float _speed)
{
	m_maxFireRate -= _speed;

	if (m_maxFireRate < 0.1f)
		m_maxFireRate = 0.1f;
}

void Player::addBomb(unsigned int _bomb)
{
	m_bomb += _bomb;

	if (m_bomb > 3)
		m_bomb = 3;
}

void Player::addLife(unsigned int _life)
{
	m_life += _life;

	if (m_life > 5)
		m_life = 5;
}

void Player::addScore(unsigned int _score)
{
	m_score += _score;
	sound_play("score");
}
