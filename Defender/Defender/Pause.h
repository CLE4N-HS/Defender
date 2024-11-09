#pragma once
#include "Window.h"

class Pause
{
public:
	Pause();
	~Pause();

	inline static bool isOpen() { return m_isOpen; }
	static void toggle();

	static void update(Window& _window);
	static void display(Window& _window);

private:
	static bool m_isOpen;
	static int m_index;
	static float m_timer;

};
