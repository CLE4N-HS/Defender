#pragma once
#include "Window.h"
#include "State.h"
#include "Player.h"

class GameOver
{
public:
	GameOver();
	~GameOver();

	static void update(Window& _window, State*& _state, Player& _player);
	static void display(Window& _window);

	static inline bool isGameOver() { return m_isGameOver; }
	static void setup(const int& _score);

private:
	static bool m_isGameOver;

	static int m_index;

	static bool m_isSavingScore;
	static int m_scoreIndex;
	static float m_scoreTimer;
	static std::string m_name;
	static float m_nameTimer;
	static bool m_nameHighlight;

};
