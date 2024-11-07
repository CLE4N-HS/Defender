#pragma once
#include "Window.h"

typedef enum {
	C_WALK,
	C_WAITING,
	C_GRABBED,
	C_GRABBED_BY_PLAYER,
	C_FALL
}Civilian_State;

class civilians
{

public:
	civilians();

	void update(Window& _window, sf::Vector2f _playerPos);
	void display(Window& _window, bool _isMainView);

	inline sf::Vector2f getCivilPos() { return m_pos; }
	inline void setCivilIsTargeted(bool _isTargeted) { m_isTargeted = _isTargeted; }
	inline bool getIsTargeted() const { return m_isTargeted; }
	inline void setCivilIsGrabbed(bool _isGrabbed) { m_isGrabbed = _isGrabbed; }
	inline void setState(Civilian_State _state) { m_state = _state; }
	inline Civilian_State getState() { return m_state; }
	/*inline void setPlayerIsGrabbed(bool _isGrabbed) { m_isGrabbedByPlayer = _isGrabbed; }
	inline bool getPlayerIsGrabbed() { return m_isGrabbedByPlayer; }*/

private:

	void shouldMove2(sf::Vector2f _centerView);

	Civilian_State m_state;
	sf::Vector2f m_pos;
	int m_direction;
	float m_timerWaiting;
	bool m_mustDie;
	bool m_isGrabbed;
	bool m_isTargeted;
	bool m_isGrabbedByPlayer;
};

