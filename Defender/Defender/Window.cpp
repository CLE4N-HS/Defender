#include "Window.h"

Window::Window() : Window("Title", sf::Style::Default)
{

}

Window::Window(const sf::String& title, sf::Uint32 style) : m_videoMode(sf::VideoMode::getDesktopMode()), m_title(title), m_style(style),
	m_view(),
	rectangle(), text(), m_renderTexture(), m_font(),
	m_framerateLimit(60), m_isDone(false), m_fullscreenTimer(0.f),
	m_event(), m_clock(), m_time(), m_deltaTime(), m_mousePos(), m_sprite(), m_texture()
{
	srand((unsigned int)time(NULL));

	createWindow();
	m_renderTexture.create(m_videoMode.width, m_videoMode.height);
	//m_renderTexture.create(7680, 1080);
	m_font.loadFromFile("../Resources/NeoTech.ttf"); // default font for now
	text.setFont(m_font);
}

Window::~Window()
{
}

void Window::update()
{
	while (m_renderWindow.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed
			|| sf::Mouse::isButtonPressed(sf::Mouse::Middle)) // TODO remove this
			m_isDone = true;
	}

	m_hasFocus = m_renderWindow.hasFocus();

	m_time = m_clock.restart();
	m_deltaTime = m_time.asSeconds();
	m_mousePos = sf::Vector2f(sf::Mouse::getPosition(m_renderWindow));

	m_fullscreenTimer += ((m_fullscreenTimer > 0.5f) ? 0.f : m_deltaTime);
	if (m_hasFocus && m_fullscreenTimer >= 0.5f && sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		toggleFullscreen();
}

void Window::display()
{
	m_renderWindow.clear();
	m_renderTexture.display();

	m_texture = m_renderTexture.getTexture();
	m_renderTexture.clear();
	m_sprite.setTexture(m_texture, true);
	m_renderWindow.draw(m_sprite);
	m_renderWindow.display();
}

bool Window::isDone() const
{
	return m_isDone;
}

bool Window::hasFocus() const
{
	return m_hasFocus;
}

float Window::getDeltaTime() const
{
	return m_deltaTime;
}

sf::Vector2f Window::getMousePos() const
{
	return m_mousePos;
}

void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	m_renderTexture.draw(drawable, states);
}

void Window::setView(const sf::Vector2f& center, const sf::FloatRect& viewport, float factor)
{
	m_view.setCenter(center);
	m_view.setSize(sf::Vector2f(1920.f, 1080.f));
	m_view.setViewport(viewport);
	m_view.zoom(factor);
	m_renderTexture.setView(m_view);
}

void Window::setView(const sf::Vector2f& center, const sf::FloatRect& viewport, float factor, sf::Vector2f size)
{
	m_view.setCenter(center);
	m_view.setSize(size);
	m_view.setViewport(viewport);
	m_view.zoom(factor);
	m_renderTexture.setView(m_view);
}

sf::Vector2f Window::viewCorrectPos(const sf::Vector2f& _pos, const bool& mainView) const
{
	return (mainView ? _pos : sf::Vector2f(_pos.x * 0.25f, _pos.y));
}

void Window::toggleFullscreen()
{
	m_fullscreenTimer = 0.f;
	m_style = (m_style == sf::Style::Fullscreen ? sf::Style::Default : sf::Style::Fullscreen);
	createWindow();
}

void Window::createWindow()
{
	m_renderWindow.create(m_videoMode, m_title, m_style);
	m_isFullscreen = (m_style == sf::Style::Fullscreen);
	m_renderWindow.setFramerateLimit(m_framerateLimit);
}
