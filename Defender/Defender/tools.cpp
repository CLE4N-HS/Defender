#include "tools.h"

float vec2fGetMagnitude(sf::Vector2f _vec)
{
    return sqrtf(_vec.x * _vec.x + _vec.y * _vec.y);
}

float vec2fGetSqrtMagnitude(sf::Vector2f _vec)
{
    return _vec.x * _vec.x + _vec.y * _vec.y;
}

void vec2fNormalize(sf::Vector2f& _vec)
{
    float magnitude = vec2fGetMagnitude(_vec);
    if (magnitude >= EPSILON)
        _vec /= magnitude;
}

sf::Vector2f vec2fMultiply(sf::Vector2f _vec, float _num)
{
    return sf::Vector2f(_vec.x * _num, _vec.y * _num);
}

sf::Vector2f vec2fMultiplyVector(sf::Vector2f _vec1, sf::Vector2f _vec2)
{
    return sf::Vector2f(_vec1.x * _vec2.x, _vec1.y * _vec2.y);
}

sf::Vector2f vec2fNormalizeValue(sf::Vector2f _vec)
{
    float magnitude = vec2fGetMagnitude(_vec);
    if (magnitude >= EPSILON)
        _vec /= magnitude;
    return _vec;
}

sf::Vector2f polarCoord(sf::Vector2f const& _a, float const& _r, float const& _teta)
{
    return sf::Vector2f(_a.x + (_r * cosf(_teta)), _a.y + (_r * sinf(_teta)));
}

int randomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

float randomFloat(float min, float max)
{
    return (float)randomInt(min, max);
}

float lerp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

float randFloat(const float& _min, const float& _max)
{
    float range = (_max - _min);
    if (range <= 0.f)
        return 0.f;
    float div = (float)RAND_MAX / range;
    return _min + (rand() / div);
}