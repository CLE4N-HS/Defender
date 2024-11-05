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
    return (float)randomInt((int)min, (int)max);
}

float lerp(float v0, float v1, float t)
{
    return (1.f - t) * v0 + t * v1;
}

float randFloat(const float& _min, const float& _max)
{
    float range = (_max - _min);
    if (range <= 0.f)
        return 0.f;
    float div = (float)RAND_MAX / range;
    return _min + (rand() / div);
}


sf::Vector2f lerpVector(sf::Vector2f v0, sf::Vector2f v1, float t)
{
    return sf::Vector2f(lerp(v0.x, v1.x, t), lerp(v0.y, v1.y, t));
}

float lerp_smooth(float v0, float v1, float t)
{
    return v0 + (v1 - v0) * (t * t * (3.f - 2.f * t));
}

sf::Color randomColor(sf::Uint8 _alpha)
{
    sf::Color c;
    c.r = (sf::Uint8)(rand() % 255);
    c.g = (sf::Uint8)(rand() % 255);
    c.b = (sf::Uint8)(rand() % 255);
    c.a = _alpha;
    return c;
}
