#pragma once
#include "Window.h"

class Multiplication
{
public:

	Multiplication();
	~Multiplication();

	static inline void addMultiplication(int _number) {m_multiplier >= 4 ? m_multiplier : m_multiplier += _number; }
	static inline int getMultiplication() { return m_multiplier; }
	static inline void resetMultiplication() { m_multiplier = 1; }

	static void displayMultiplication(Window& _window);
private:
	static int m_multiplier;
};

