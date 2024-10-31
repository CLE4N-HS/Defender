#include "Master.h"

Master::Master() : m_window("Defender", sf::Style::Default), m_stateManager(), m_newState(nullptr)
{
}

Master::~Master()
{
}

void Master::loop()
{
	while (!m_window.isDone())
	{
		if (m_newState)
		{
			m_stateManager.changeState(m_newState);
			m_newState = nullptr;
		}


		m_window.update();

		if (m_window.hasFocus())
			m_stateManager.update(m_window, m_newState);

		m_stateManager.display(m_window);

		m_window.display();
	}
}
