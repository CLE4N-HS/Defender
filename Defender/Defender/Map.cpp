#include "Map.h"
#include "textureManager.h"

Map::Map() : m_pos1(960.f, 172.f * 0.5f + 540.f), m_pos2(960.f, 172.f * 0.5f + 540.f)
{
}

Map::~Map()
{
}

void Map::update(Window& _window, sf::Vector2f _playerPos)
{
	float playerMapPos = (float)((int)(_playerPos.x - 3840.f) / 7680);

	m_pos1.x = 7680.f * playerMapPos;
	m_pos2.x = m_pos1.x + ((_playerPos.x > (m_pos1.x + 3840.f)) ? 7680.f : -7680.f);
}

void Map::display(Window& _window, bool mainView, sf::Vector2f _playerPos)
{
	// map
	_window.rectangle.setTexture(tex_getTexture("map"), true);
	_window.rectangle.setPosition(_window.viewCorrectPos(m_pos1, mainView));
	_window.rectangle.setOrigin(sf::Vector2f(0.f, 540.f));
	_window.rectangle.setSize(sf::Vector2f(7680.f, 1080.f));
	_window.rectangle.setScale(_window.viewCorrectScale(sf::Vector2f(1.f, 1.f), mainView));
	_window.draw(_window.rectangle);

	_window.rectangle.setPosition(_window.viewCorrectPos(m_pos2, mainView));
	_window.draw(_window.rectangle);


	_window.rectangle.setScale(sf::Vector2f(1.f, 1.f));
}
