#pragma once
#include "Window.h"
#include "State.h"

class Options
{
public:
	Options();
	~Options();

	inline static bool isOpen() { return m_isOpen; }
	inline static int getSongVolume() { return m_songVolume; }
	inline static int getMusicVolume() { return m_musicVolume; }

	static void toggle();
	static void addSongVolume(int _value);
	static void addMusicVolume(int _value);

	static void update(Window& _window, const bool& _isInMenu, State*& _state);
	static void display(Window& _window);

private:
	static bool m_isOpen;
	static int m_songVolume;
	static int m_musicVolume;
	static int m_index;

};
