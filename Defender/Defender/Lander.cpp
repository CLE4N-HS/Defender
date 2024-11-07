#include "Lander.h"
#include "textureManager.h"
#include "enemiesBullets.h"

Lander::Lander()
{
	pos = sf::Vector2f(randomFloat(0.0f,1920.f), randomFloat(0.0f,1080.f));
	velocity = sf::Vector2f(300.f, 300.f);
	state = E_GODOWN;		           //the current state
	attackTimer = rand() % 5 + 1;          //timer bewteen each attack
	m_timerEachMoveY = rand() % 4 + 1;     //timer between each Y movement 
	m_timerDuringMoveY = rand() % 2 + 1;   //timer during Y movement 
	m_directionX = rand() % 2;          //direction x of the lander
	m_directionY = rand() % 2;          //direction y of the lander
	m_timerToCatch = randomFloat(5.f, 20.f);
}

Lander::Lander(sf::Vector2f _pos, Window& _window)
{
	pos = sf::Vector2f(randomFloat( _window.viewCurrentPos(_pos).x +1920.f, _window.viewCurrentPos(_pos).x - 1920.f) , 0.0f);
	//pos = sf::Vector2f(_window.viewCurrentPos(_pos).x - 960.f, 0.0f);
	//pos = sf::Vector2f(_pos.x - 1920.f, 0.0f);
	velocity = sf::Vector2f(300.f, 300.f);
	state = E_GODOWN;		           //the current state
	attackTimer = rand() % 5 + 1;          //timer bewteen each attack
	m_timerEachMoveY = rand() % 4 + 1;     //timer between each Y movement 
	m_timerDuringMoveY = rand() % 2 + 1;   //timer during Y movement 
	m_directionX = rand() % 2;          //direction x of the lander
	m_directionY = rand() % 2;          //direction y of the lander
	m_timerToCatch = randomFloat(5.f, 20.f);
	targetCivil = nullptr;
	haveGrabbedCivil = false;
}

void Lander::update(Window& _window, Player _player, std::list<Bullets*>& _bulList)
{
	float delta = _window.getDeltaTime();  //difference between player and enemy = 3500
	sf::Vector2f tmpViewPos = _window.getViewPos();
	sf::Vector2f tmpPlayerPos = _player.getPos();
	shouldMove(tmpViewPos);

	if (state == E_NATURAL || state == E_GODOWN)
	{
		m_timerToCatch -= delta;
		if (m_timerToCatch <= 0.0f)
			state = E_CHASE;
	}

	if (state != E_MUTANT)
	{
		if (_player.getLife() > 0)
		{
			if (attackTimer > 0.0f)
				attackTimer -= delta;
			else
			{
				_bulList.push_back(new enemiesBullets(pos, vec2fNormalizeValue(sf::Vector2f(tmpPlayerPos - pos)), sf::Vector2f(500.f, 500.f)));
				attackTimer = rand() % 5 + 1;
			}
		}
	}

	if (state == E_NATURAL)
	{
		//lander's movements

		if (m_directionX == 0) pos.x -= velocity.x * delta;
		if (m_directionX == 1) pos.x += velocity.x * delta;

		if(m_timerEachMoveY > 0.0f)
			m_timerEachMoveY -= delta;

		if (m_timerEachMoveY <= 0.0f)
		{
			m_timerDuringMoveY -= delta;
			if (m_directionY == 0) pos.y -= velocity.y * delta;
			if (m_directionY == 1) pos.y += velocity.y * delta;

			if (m_timerDuringMoveY <= 0.0f)
			{
				m_timerDuringMoveY = rand() % 2 + 1;
				m_timerEachMoveY = rand() % 4 + 1;
				m_directionY = rand() % 2;
			}
		}
		
		if (pos.y >= 800.f) m_directionY = 0;
		if (pos.y <= 172.f + 16.f) m_directionY = 1;


	}
	else if (state == E_GODOWN)
	{
		if (m_directionX == 0) pos.x -= velocity.x * delta;
		if (m_directionX == 1) pos.x += velocity.x * delta;

		if (pos.y < 700.f) pos.y += velocity.y * delta;
		else state = E_NATURAL;
	}
	else if (state == E_CHASE)
	{
		if (targetCivil)
		{
			pos.y -= 200.f * delta;
		}
	}
	else if (state == E_MUTANT)
	{
		sf::Vector2f pPosNor = tmpPlayerPos - pos;
		vec2fNormalize(pPosNor);


		pPosNor = sf::Vector2f(pPosNor.x * velocity.x * delta, pPosNor.y * velocity.y * delta);
		pos += pPosNor;
	}
}

void Lander::display(Window& _window, bool _isMainView)
{
	_window.rectangle.setTexture(tex_getTexture("all"));
	if(_isMainView)
	{
		if(state != E_MUTANT)
			_window.rectangle.setTextureRect(tex_getAnimRect("all", "lander"));
		else
			_window.rectangle.setTextureRect(tex_getAnimRect("all", "mutant"));
	}
	else
		_window.rectangle.setTextureRect(tex_getAnimRect("all", "babyLander"));
	_window.rectangle.setPosition(_window.viewCorrectPos(pos, _isMainView));
	_window.rectangle.setSize(sf::Vector2f(36.f, 32.f));
	_window.rectangle.setOrigin(sf::Vector2f(18.f, 16.f));
	colRect = sf::FloatRect(pos - _window.rectangle.getOrigin(), _window.rectangle.getSize());
	_window.draw(_window.rectangle);
}

sf::FloatRect Lander::getEnemyColRect() const
{
	return colRect;
}

void Lander::addBullet(sf::Vector2f _pos)
{
}

sf::Vector2f createVector(sf::Vector2f _pos1, sf::Vector2f _pos2)
{
	return sf::Vector2f(_pos2.x - _pos1.x, _pos2.y - _pos1.y);
}

void Lander::shouldMove(sf::Vector2f _centerView) // put the center of the mapView
{
	sf::Vector2f p_ePos = createVector(_centerView, pos);
	float magnitude = vec2fGetSqrtMagnitude(p_ePos);

	if (magnitude > 12250000.f)
	{
		if (p_ePos.x > 1) pos.x -= 7000.f;
		else pos.x += 7000.f;
	}

}
