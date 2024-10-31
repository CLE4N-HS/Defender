/*
 * Copyright (c) 2024, Hugo
 *
 * Ce code a été créé en langage C puis traduit en C++ en 2024 par Hugo Miceli
 * Tous droits réservés.
 *
 * Toute utilisation, distribution, ou modification de ce code est soumise à
 * l'accord des auteurs.
 */

#pragma once
#include "tools.h"
#include "Window.h"

typedef enum {
	CIRCLE,
	SQUARE,
	ANIMATION_PARTICLE
}particlesType;

typedef enum {
	LOADING,
	STUN,
	LEAF,
	GAIN,
	WALK,
	DUST,
	FEATHER,
	GRASS,
	WATER,
	FIRE,
	prt_HEART,
	CATCH,
	POT,
	DAMAGE
}wichParticles;

typedef struct {
	sf::Vector2f pos;
	sf::Color colorStart;
	sf::Color colorEnd;
	float timeToDie;
	float timer;
	float timerFirefly;
	sf::Texture* texture;
	float radiusStart;
	float radiusEnd;
	sf::Vector2f forward;
	sf::Vector2f sizeStart;
	sf::Vector2f sizeEnd;
	float velocity;
	float rotateVelocity;
	particlesType particleType;
	float teta;
	float width;
	float height;
	bool gravity;
	bool levitation;
	bool isGenerative;
	bool hasGenerate;
	bool hasFriction;
	bool isInFront;
	float timerSpawn;
	float outlineThickness;
	sf::Color outlineColorStart;
	sf::Color outlineColorEnd;
	int countPoint;
	int frameX;
	float animTimer;
	char* animName;
	wichParticles wichParticles;
}particles;

/// <summary>
/// init the particle manager
/// </summary>
void prt_InitParticles();

/// <summary>
/// create particles at a given position
/// </summary>
/// <param name="_spawnPos">the particle spawn pos</param>
/// <param name="_particlesAmount">the amount of particles</param>
/// <param name="_colorStart">the color when the particle spawn</param>
/// <param name="_colorEnd">the color when the particle die</param>
/// <param name="_timeToDie">the time before the particle die</param>
/// <param name="_texture">Texture of the particle (can be null)</param>
/// <param name="_radiusStart">the radius of the circle particle/the size of the square particle when it spawns</param>
/// <param name="_radiusEnd">the radius of the circle particle/the size of the square particle when it die</param>
/// <param name="_angleMin">the min hook_Angle in the direction where the particle will go</param>
/// <param name="_angleMax">the max hook_Angle in the direction where the particle will go</param>
/// <param name="_velocity">the particle velocity</param>
/// <param name="_rotateVelocity">the particle rotation velocity</param>
/// <param name="_outline">the outline thickness</param>
/// <param name="_outlineColorStart">the outline color when it spawns</param>
/// <param name="_outlineColorEnd">the outline color when it dies</param>
/// <param name="_partType">the particle type (circle square or sprite)</param>
/// <param name="_hasGravity">does the particle has gravity apllied to it</param>
/// <param name="_isGenerative">is the particle generating other smaller particles</param>
/// <param name="_isSpriteRecolored">is the sprite recolored (if yes the color start and end of the begining will be applied)</param>
void createParticles(sf::Vector2f _spawnPos, int _particlesAmount, sf::Color _colorStart, sf::Color _colorEnd, float _timeToDie,
	sf::Texture* _texture, float _radiusStart, float _radiusEnd, float _angleMin, float _angleMax,
	float _velocity, float _rotateVelocity, float _outline, sf::Color _outlineColorStart, sf::Color _outlineColorEnd, particlesType _partType,
	bool _hasGravity, bool _levitation, bool _isGenerative, int _countPoint, sf::Vector2f _sizeStart, sf::Vector2f _sizeEnd, bool _hasFriction, bool _isInFront);

/// <summary>
/// create circle particles at a given position
/// </summary>
/// <param name="_spawnPos">the particle spawn pos</param>
/// <param name="_particlesAmount">the amount of particles</param>
/// <param name="_countPoint">the amount of side for polygon <=3 for circle</param>
/// <param name="_colorStart">the color when the particle spawn</param>
/// <param name="_colorEnd">the color when the particle die</param>
/// <param name="_timeToDie">the time before the particle die</param>
/// <param name="_radiusStart">the radius of the circle particle when it spawns</param>
/// <param name="_radiusEnd">the radius of the circle particle when it die</param>
/// <param name="_angleMin">the min hook_Angle in the direction where the particle will go</param>
/// <param name="_angleMax">the max hook_Angle in the direction where the particle will go</param>
/// <param name="_velocity">the particle velocity</param>
/// <param name="_outline">the outline thickness</param>
/// <param name="_outlineColorStart">the outline color when it spawns</param>
/// <param name="_outlineColorEnd">the outline color when it dies</param>
/// <param name="_hasGravity">does the particle has gravity apllied to it</param>
/// <param name="_isGenerative">is the particle generating other smaller particles</param>
void prt_CreateCircleParticles(sf::Vector2f _spawnPos, int _particlesAmount, int _countPoint, sf::Color _colorStart, sf::Color _colorEnd, float _timeToDie,
	float _radiusStart, float _radiusEnd, float _angleMin, float _angleMax, float _velocity, float _rotateVelocity, float _outline,
	sf::Color _outlineColorStart, sf::Color _outlineColorEnd, bool hasGravity, bool _levitation, bool _isGenerative, sf::Texture* _texture,
	bool _hasFriction, bool _isInFront, wichParticles _wichParticles);

/// <summary>
/// create square particles at a given position
/// </summary>
/// <param name="_spawnPos">the particle spawn pos</param>
/// <param name="_particlesAmount">the amount of particles</param>
/// <param name="_colorStart">the color when the particle spawn</param>
/// <param name="_colorEnd">the color when the particle die</param>
/// <param name="_timeToDie">the time before the particle die</param>
/// <param name="_radiusStart">the size of the square particle when it spawns</param>
/// <param name="_radiusEnd">the size of the square particle when it die</param>
/// <param name="_angleMin">the min hook_Angle in the direction where the particle will go</param>
/// <param name="_angleMax">the max hook_Angle in the direction where the particle will go</param>
/// <param name="_velocity">the particle velocity</param>
/// <param name="_rotateVelocity">the particle rotation velocity</param>
/// <param name="_outline">the outline thickness</param>
/// <param name="_outlineColorStart">the outline color when it spawns</param>
/// <param name="_outlineColorEnd">the outline color when it dies</param>
/// <param name="_hasGravity">does the particle has gravity apllied to it</param>
/// <param name="_isGenerative">is the particle generating other smaller particles</param>
void prt_CreateSquareParticles(sf::Vector2f _spawnPos, int _particlesAmount, sf::Color _colorStart, sf::Color _colorEnd, float _timeToDie,
	sf::Vector2f _sizeStart, sf::Vector2f _sizeEnd, float _angleMin, float _angleMax, float _velocity, float _rotateVelocity, float _outline,
	sf::Color _outlineColorStart, sf::Color _outlineColorEnd, bool _hasGravity, bool _levitation, bool _isGenerative, sf::Texture* _texture
	, bool _hasFriction, bool _isInFront, wichParticles _wichParticles);

/// <summary>
/// update every particles
/// </summary>
void prt_UpdateParticles(float const& _dt);

/// <summary>
/// display every particles
/// </summary>
/// <param name="_window">the current window</param>
void prt_DisplayParticlesBehind(Window& _window, float const& _dt);

void prt_DisplayParticlesInFront(Window& _window, float const& _dt);


void prt_clear();