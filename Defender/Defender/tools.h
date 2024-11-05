#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <fstream>
#include <map>
#include <list>
#include <iterator>

#define EPSILON ((float)1e-6)
#define DEG2RAD ((float)0.01745329f)

float vec2fGetMagnitude(sf::Vector2f _vec);
float vec2fGetSqrtMagnitude(sf::Vector2f _vec);
void vec2fNormalize(sf::Vector2f& _vec);
sf::Vector2f vec2fMultiply(sf::Vector2f _vec, float _num);
sf::Vector2f vec2fMultiplyVector(sf::Vector2f _vec1, sf::Vector2f _vec2);
sf::Vector2f vec2fNormalizeValue(sf::Vector2f _vec);
sf::Vector2f polarCoord(sf::Vector2f const& _a, float const& _r, float const& _teta);
int randomInt(int min, int max);
float randomFloat(float min, float max);
float lerp(float v0, float v1, float t);
float randFloat(const float& _min, const float& _max);
sf::Vector2f lerpVector(sf::Vector2f v0, sf::Vector2f v1, float t);
float lerp_smooth(float v0, float v1, float t);
sf::Color randomColor(sf::Uint8 _alpha = 255);

