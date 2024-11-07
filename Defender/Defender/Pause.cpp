#include "Pause.h"

bool Pause::m_isOpen = false;
int Pause::m_index = 0;

Pause::Pause()
{
}

Pause::~Pause()
{
}

void Pause::toggle()
{
	m_isOpen = !m_isOpen;

	m_index = 0;
}

void Pause::update(Window& _window)
{

}

void Pause::display(Window& _window)
{

}
