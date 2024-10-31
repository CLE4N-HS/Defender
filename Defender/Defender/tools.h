#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <fstream>
#include <map>

#define EPSILON ((float)1e-6)
#define DEG2RAD ((float)0.01745329f)

float vec2fGetMagnitude(sf::Vector2f _vec);
void vec2fNormalize(sf::Vector2f& _vec);
sf::Vector2f polarCoord(sf::Vector2f const& _a, float const& _r, float const& _teta);
int randomInt(int min, int max);
float randomFloat(float min, float max);
float lerp(float v0, float v1, float t);
