#include "particleManager.h"
#include <list>
#include "ressourcesManager.h"
#include "textureManager.h"

std::list<particles> particlesList;

sf::CircleShape* circleShpParticles;
sf::RectangleShape* rectParticles;

sf::RenderStates renderStateParticles;

sf::Color color_lerp_no_opacity(sf::Color v0, sf::Color v1, float t)
{
	sf::Color tmp;
	tmp.r = (sf::Uint8)((1.f - t) * (float)v0.r + t * (float)v1.r);
	tmp.g = (sf::Uint8)((1.f - t) * (float)v0.g + t * (float)v1.g);
	tmp.b = (sf::Uint8)((1.f - t) * (float)v0.b + t * (float)v1.b);
	tmp.a = v0.a;
	//tmp.a = (sf::Uint8)(1.f - t) * v0.a;
	return tmp;
}

void prt_InitParticles()
{

}

void createParticles(sf::Vector2f _spawnPos, int _particlesAmount, sf::Color _colorStart, sf::Color _colorEnd, float _timeToDie,
	sf::Texture* _texture, float _radiusStart, float _radiusEnd, float _angleMin, float _angleMax,
	float _velocity, float _rotateVelocity, float _outline, sf::Color _outlineColorStart, sf::Color _outlineColorEnd, particlesType _partType,
	bool _hasGravity, bool _levitation, bool _isGenerative, int _countPoint, sf::Vector2f _sizeStart, sf::Vector2f _sizeEnd, bool _hasFriction, bool _isInFront, wichParticles _wichParticles)
{
	for (int i = 0; i < _particlesAmount; i++)
	{
		particles tempParticle;
		tempParticle.colorStart = _colorStart;
		tempParticle.animName = NULL;
		tempParticle.colorEnd = _colorEnd;
		tempParticle.radiusStart = _radiusStart;
		tempParticle.radiusEnd = _radiusEnd;
		tempParticle.timer = 0.f;
		tempParticle.timerFirefly = 0.f;
		tempParticle.teta = 0.f;
		tempParticle.texture = _texture;
		tempParticle.pos = _spawnPos;
		tempParticle.forward = polarCoord(sf::Vector2f(0.f, 0.f), 1.f, randomFloat(_angleMin, _angleMax) * DEG2RAD);
		tempParticle.timeToDie = _timeToDie;
		tempParticle.velocity = _velocity;
		tempParticle.rotateVelocity = _rotateVelocity;
		tempParticle.particleType = _partType;
		tempParticle.gravity = _hasGravity;
		tempParticle.levitation = _levitation;
		tempParticle.isGenerative = _isGenerative;
		tempParticle.hasGenerate = false;
		tempParticle.timerSpawn = 0.f;
		tempParticle.outlineThickness = _outline;
		tempParticle.outlineColorStart = _outlineColorStart;
		tempParticle.outlineColorEnd = _outlineColorEnd;
		tempParticle.countPoint = _countPoint;
		tempParticle.sizeStart = _sizeStart;
		tempParticle.sizeEnd = _sizeEnd;
		tempParticle.hasFriction = _hasFriction;
		tempParticle.isInFront = _isInFront;
		tempParticle.wichParticles = _wichParticles;

		tempParticle.frameX = 0;
		tempParticle.animTimer = 0.f;


		particlesList.push_back(tempParticle);
	}
}

void prt_CreateCircleParticles(sf::Vector2f _spawnPos, int _particlesAmount, int _countPoint, sf::Color _colorStart, sf::Color _colorEnd, float _timeToDie, float _radiusStart,
	float _radiusEnd, float _angleMin, float _angleMax, float _velocity, float _rotateVelocity, float _outline, sf::Color _outlineColorStart, sf::Color _outlineColorEnd,
	bool _hasGravity, bool _levitation, bool _isGenerative, sf::Texture* _texture, bool _hasFriction, bool _isInFront, wichParticles _wichParticles)
{
	createParticles(_spawnPos, _particlesAmount, _colorStart, _colorEnd, _timeToDie, _texture, _radiusStart, _radiusEnd, _angleMin, _angleMax, _velocity,
		_rotateVelocity, _outline, _outlineColorStart, _outlineColorEnd, CIRCLE, _hasGravity, _levitation, _isGenerative, _countPoint, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), _hasFriction, _isInFront, _wichParticles);
}

void prt_CreateSquareParticles(sf::Vector2f _spawnPos, int _particlesAmount, sf::Color _colorStart, sf::Color _colorEnd, float _timeToDie,
	sf::Vector2f _sizeStart, sf::Vector2f _sizeEnd, float _angleMin, float _angleMax, float _velocity, float _rotateVelocity, float _outline,
	sf::Color _outlineColorStart, sf::Color _outlineColorEnd, bool _hasGravity, bool _levitation, bool _isGenerative, sf::Texture* _texture, bool _hasFriction, bool _isInFront, wichParticles _wichParticles)
{
	createParticles(_spawnPos, _particlesAmount, _colorStart, _colorEnd, _timeToDie, _texture, 0.f, 0.f, _angleMin, _angleMax, _velocity,
		_rotateVelocity, _outline, _outlineColorStart, _outlineColorEnd, SQUARE, _hasGravity, _levitation, _isGenerative, 0, _sizeStart, _sizeEnd, _hasFriction, _isInFront, _wichParticles);
}

void prt_UpdateParticles(float const& _dt)
{

	float dt = _dt;

	for (std::list<particles>::iterator it = particlesList.begin(); it != particlesList.end();)
	{
		it->timer += dt;
		it->timerFirefly += dt;

		float tea = it->timer / it->timeToDie;
		float size = lerp(it->radiusStart, it->radiusEnd, tea);
		sf::Vector2f rectSize = sf::Vector2f(lerp(it->sizeStart.x, it->sizeEnd.x, tea), lerp(it->sizeStart.y, it->sizeEnd.y, tea));
		if (it->isGenerative && tea > 0.5f && !it->hasGenerate)
		{
			createParticles(it->pos, 20, it->colorStart, it->colorEnd, it->timeToDie / 2.f, it->texture, size / 1.5f,
				it->radiusEnd / 2.f, 0.f, 360.f, it->velocity * 2.f, it->rotateVelocity * 2.f, it->outlineThickness, it->outlineColorStart,
				it->outlineColorEnd, it->particleType, it->gravity, it->levitation, false, it->countPoint,
				sf::Vector2f(rectSize.x / 1.5f, rectSize.y / 1.5f), sf::Vector2f(it->sizeEnd.x / 2.f, it->sizeEnd.y / 2.f), it->hasFriction, it->isInFront, it->wichParticles);
			it->hasGenerate = true;
		}
		//Gravity test
		if (it->gravity)
			it->forward.y += 2.f * dt;
		if (it->levitation)
			it->forward.y -= 2.f * dt;

		if (it->hasFriction) {
			it->forward.x *= powf(0.1f, dt);
			it->forward.y *= powf(0.1f, dt);
		}

		it->pos += it->forward * it->velocity * dt;

		it->teta += it->rotateVelocity * dt;

		if (it->timer > it->timeToDie)
			it = particlesList.erase(it);
		else
			it++;
	}
}

void prt_DisplayParticlesBehind(Window& _window, float const& _dt)
{
	float dt = _dt;
	for (auto it = particlesList.begin(); it != particlesList.end(); ++it)
	{
		if (!it->isInFront)
		{
			float tea = it->timer / it->timeToDie;
			sf::Color partColor = color_lerp_no_opacity(it->colorStart, it->colorEnd, tea);
			sf::Color partOutlineColor = color_lerp_no_opacity(it->outlineColorStart, it->outlineColorEnd, tea);
			float size = lerp(it->radiusStart, it->radiusEnd, tea);
			sf::Vector2f rectSize = sf::Vector2f(lerp(it->sizeStart.x, it->sizeEnd.x, tea), lerp(it->sizeStart.y, it->sizeEnd.y, tea));

			if (it->particleType == CIRCLE) {
				sf::CircleShape circleShpParticles(size);
				if (it->countPoint >= 3)
					circleShpParticles.setPointCount(it->countPoint);

				circleShpParticles.setFillColor(sf::Color::White);
				circleShpParticles.setPosition(it->pos);
				circleShpParticles.setOrigin(size / 2.f, size / 2.f);
				circleShpParticles.setRotation(it->teta);
				circleShpParticles.setOutlineThickness(it->outlineThickness);
				circleShpParticles.setOutlineColor(partOutlineColor);

				if (it->texture == nullptr) {
					circleShpParticles.setFillColor(partColor);
					_window.draw(circleShpParticles);
				}
				else {
					circleShpParticles.setTexture(it->texture);
					circleShpParticles.setOutlineThickness(0.f);
					
					_window.draw(circleShpParticles);
				}
			}
			else if (it->particleType == SQUARE) {
				sf::RectangleShape rectParticles(rectSize);
				rectParticles.setOrigin(rectSize.x / 2.f, rectSize.y / 2.f);
				rectParticles.setFillColor(sf::Color::White);
				rectParticles.setRotation(it->teta);
				rectParticles.setPosition(it->pos);
				rectParticles.setOutlineThickness(it->outlineThickness);
				rectParticles.setOutlineColor(partOutlineColor);

				if (it->texture == nullptr) {
					rectParticles.setFillColor(partColor);
					_window.draw(rectParticles);
				}
				else {
					rectParticles.setTexture(it->texture);
					rectParticles.setOutlineThickness(0.f);
					_window.draw(rectParticles);
					
				}
			}
		}
	}
}

void prt_DisplayParticlesInFront(Window& _window, float const& _dt)
{
	float dt = _dt;

	for (auto it = particlesList.begin(); it != particlesList.end(); ++it)
	{
		if (it->isInFront)
		{
			float tea = it->timer / it->timeToDie;
			sf::Color partColor = color_lerp_no_opacity(it->colorStart, it->colorEnd, tea);
			sf::Color partOutlineColor = color_lerp_no_opacity(it->outlineColorStart, it->outlineColorEnd, tea);
			float size = lerp(it->radiusStart, it->radiusEnd, tea);
			sf::Vector2f rectSize = sf::Vector2f(lerp(it->sizeStart.x, it->sizeEnd.x, tea), lerp(it->sizeStart.y, it->sizeEnd.y, tea));

			if (it->particleType == CIRCLE) {
				sf::CircleShape circleShpParticles(size);
				if (it->countPoint >= 3)
					circleShpParticles.setPointCount(it->countPoint);

				circleShpParticles.setFillColor(sf::Color::White);
				circleShpParticles.setPosition(it->pos);
				circleShpParticles.setOrigin(size, size);
				circleShpParticles.setRotation(it->teta);
				circleShpParticles.setOutlineThickness(it->outlineThickness);
				circleShpParticles.setOutlineColor(partOutlineColor);

				if (it->texture == nullptr) {
					circleShpParticles.setFillColor(partColor);
					_window.draw(circleShpParticles);
				}
				else {
					circleShpParticles.setTexture(it->texture);
					circleShpParticles.setOutlineThickness(0.f);
					_window.draw(circleShpParticles);
				}
			}
			else if (it->particleType == SQUARE) {
				sf::RectangleShape rectParticles(rectSize);
				rectParticles.setOrigin(rectSize.x / 2.f, rectSize.y / 2.f);
				rectParticles.setFillColor(sf::Color::White);
				rectParticles.setRotation(it->teta);
				rectParticles.setPosition(it->pos);
				rectParticles.setOutlineThickness(it->outlineThickness);
				rectParticles.setOutlineColor(partOutlineColor);

				if (it->texture == nullptr) {
					rectParticles.setFillColor(partColor);
					_window.draw(rectParticles);
				}
				else {
					rectParticles.setTexture(it->texture);
					rectParticles.setOutlineThickness(0.f);
					_window.draw(rectParticles);
			
				}
			}
		}
	}
}

void prt_clear()
{

	particlesList.clear();
}