#include "civilians.h"
#include "textureManager.h"

civilians::civilians()
{

	m_pos = sf::Vector2f(randomFloat(0, 1920.f * 3.f), 980.f);
	m_isGrabbed = false;
	m_isTargeted = false;
	m_timerWaiting = 0.0f;
	m_mustDie = false;
	m_direction = rand() % 2;

	int tmp2 = rand() % 2;
	if (tmp2 == 0) m_state = C_WAITING;
	else m_state = C_WALK;

}

void civilians::update(Window& _window)
{
	float delta = _window.getDeltaTime();
	sf::Vector2f tmpViewPos = _window.getViewPos();
	shouldMove2(tmpViewPos);
	m_timerWaiting -= delta;
	/*for (auto i = m_civiliansList.begin(); i != m_civiliansList.end();)
	{
		(*i)->timerWaiting -= delta;

		switch (m_state)
		{
		case C_WAITING:
			if ((*i)->timerWaiting <= 0.0f)
			{
				m_state = C_WALK;
			}
			break;
		case C_WALK:
			
			if ((*i)->timerWaiting <= 0.0f)
			{
				m_state = C_WALK;
			}
			break;
		case C_GRABBED:

			break;
		default:

			break;
		}

		if (m_mustDie)
		{
			i = m_civiliansList.erase(i);
		}
		else
			i++;
	}*/

	/*for (auto i : m_civiliansList)
	{

	}*/

	switch (m_state)
	{
	case C_WAITING:
		if (m_timerWaiting <= 0.0f)
		{
			m_state = C_WALK;
			m_direction = rand() % 2;
			m_timerWaiting = randomFloat(0.5f, 5.f);
		}
		break;
	case C_WALK:
		if (m_direction == 0)
			m_pos.x += 50.f * delta;
		else
			m_pos.x -= 50.f * delta;
		if (m_timerWaiting <= 0.0f)
		{
			m_state = C_WAITING;
			m_timerWaiting = randomFloat(0.5f, 5.f);
		}
		break;
	case C_GRABBED:
		
		m_pos.y -= 200.f;
		break;
	case C_FALL:

		m_pos.y += 300.f;
		break;
	default:
		m_state = C_WAITING;
		break;
	}
		
}

void civilians::display(Window& _window, bool _isMainView)
{
	
	_window.rectangle.setTexture(tex_getTexture("all"));

	_window.rectangle.setTextureRect(tex_getAnimRect("all", "civilian"));
	_window.rectangle.setPosition(_window.viewCorrectPos(m_pos, _isMainView));
	_window.rectangle.setSize(sf::Vector2f(12.f, 32.f));
	_window.rectangle.setOrigin(sf::Vector2f(6.f, 16.f));

	_window.draw(_window.rectangle);
}

sf::Vector2f createVector2(sf::Vector2f _pos1, sf::Vector2f _pos2)
{
	return sf::Vector2f(_pos2.x - _pos1.x, _pos2.y - _pos1.y);
}

void civilians::shouldMove2(sf::Vector2f _centerView)
{
	sf::Vector2f p_cPos = createVector2(_centerView, m_pos);
	float magnitude = vec2fGetSqrtMagnitude(p_cPos);

	if (magnitude > 12250000.f)
	{
		if (p_cPos.x > 1) m_pos.x -= 7000.f;
		else m_pos.x += 7000.f;
	}
}

