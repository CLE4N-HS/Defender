#pragma once
#include "Window.h"

typedef enum {
	C_WALK,
	C_WAITING,
	C_GRABBED,
	C_FALL
}Civilian_State;

class civilians
{

public:
	civilians();

	void update(Window& _window);
	void display(Window& _window, bool _isMainView);

	inline sf::Vector2f getCivilPos() { return m_pos; }
	inline void setCivilIsTargeted(bool _isTargeted) { m_isTargeted = _isTargeted; }
	inline bool getIsTargeted() const { return m_isTargeted; }

private:

	void shouldMove2(sf::Vector2f _centerView);

	Civilian_State m_state;
	sf::Vector2f m_pos;
	int m_direction;
	float m_timerWaiting;
	bool m_mustDie;
	bool m_isGrabbed;
	bool m_isTargeted;
};

