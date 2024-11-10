#include "Bomb.h"
#include "controller.h"
#include "particleManager.h"
#include "BonusManager.h"
#include "soundManager.h"

Bomb::Bomb() : m_timer(0.f)
{
}

Bomb::~Bomb()
{
}

void Bomb::update(Window& _window, std::list<Enemies*>& _enemies, Player& _player)
{
	if (m_timer < 10.f)
		m_timer += _window.getDeltaTime();

	if (m_timer < 1.f)
		return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) ||
		Gamepad_isButtonPressed(0, gamepadXBOX::Y))
	{

		m_timer = 0.f;

		_player.useBomb(1);
		sound_play("bomb");

		const sf::Vector2f centerPos = _player.getViewCenterPos();

		for (std::list<Enemies*>::iterator ite = _enemies.begin(); ite != _enemies.end();)
		{
			if (fabsf((*ite)->getEnemyPos().x - centerPos.x) < 960.f)
			{
				if (rand() % 5 == 0)
					BonusManager::createRandomBonus((*ite)->getEnemyPos());
				civilians* tmpCivil = (*ite)->getTargetedCivil();
				if (tmpCivil != nullptr)
				{
					if (tmpCivil->getIsGrabbed() == true)
						(*ite)->getTargetedCivil()->setState(C_FALL);
					(*ite)->getTargetedCivil()->setCivilIsTargeted(false);
					(*ite)->getTargetedCivil()->setCivilIsGrabbed(false);
				}
				if ((*ite)->getEnemyState() == E_MUTANT)
				{
					for (int o = 0; o < 10; o++)
					{
						prt_CreateSquareParticles((*ite)->getEnemyPos(), 1, sf::Color::Green, sf::Color::Magenta, 0.5f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(10.f, 10.f), o * 36.f, o * 36.f, 200.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
					}
				}
				else
				{
					for (int o = 0; o < 10; o++)
					{
						prt_CreateSquareParticles((*ite)->getEnemyPos(), 1, sf::Color::White, sf::Color::Green, 0.5f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(10.f, 10.f), o * 36.f, o * 36.f, 200.f, 0.0f, 0.0f, sf::Color::White, sf::Color::White, false, false, false, nullptr, false, false, LOADING);
					}
				}
				_player.addScore((*ite)->getScoreValue());
				ite = _enemies.erase(ite);

			}
			else
			{
				ite++;
			}

		}
	}
}
