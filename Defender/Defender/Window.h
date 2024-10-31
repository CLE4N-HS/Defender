#pragma once
#include "tools.h"

class Window
{
public:
	Window();
	Window(const sf::String& title, sf::Uint32 style = sf::Style::Default);
	~Window();

	void update();
	void display();

	bool isDone() const;
	bool hasFocus() const;
	float getDeltaTime() const;
	sf::Vector2f getMousePos() const;
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

	sf::RectangleShape rectangle;
	sf::Text text;

private:
	sf::RenderWindow m_renderWindow;
	sf::RenderTexture m_renderTexture;
	sf::Font m_font;

	sf::VideoMode m_videoMode;
	sf::String m_title;
	sf::Uint32 m_style;
	bool m_isFullscreen;
	unsigned int m_framerateLimit;
	bool m_isDone;
	bool m_hasFocus;
	float m_fullscreenTimer;

	sf::Event m_event;
	sf::Clock m_clock;
	sf::Time m_time;
	float m_deltaTime;
	sf::Vector2f m_mousePos;

	sf::Sprite m_sprite;
	sf::Texture m_texture;


	void toggleFullscreen();
	void createWindow();

};
