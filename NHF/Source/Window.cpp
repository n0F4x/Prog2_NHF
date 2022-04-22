#include "Window.hpp"


sf::RenderWindow Window::_window;
float Window::_FPS = 60.f;
sf::Clock Window::_clock;


void Window::init() {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.sRgbCapable = true;

	_window.create(sf::VideoMode::getDesktopMode(), "My Game", sf::Style::Fullscreen, settings);

	_window.setVerticalSyncEnabled(true);
	_window.setKeyRepeatEnabled(false);
}


sf::Vector2f Window::getSize() {
	return sf::Vector2f{ _window.getSize() };
}

sf::FloatRect Window::getLocalBounds() {
	return sf::FloatRect{ 0.f, 0.f, getSize().x, getSize().y };
}

void Window::close() { _window.close(); }

bool Window::isOpen() {
	while (_clock.getElapsedTime().asMilliseconds() < 1000.f / _FPS)
		;
	_clock.restart();
	return _window.isOpen();
}

bool Window::pollEvent(sf::Event& event) {
	return _window.pollEvent(event);
}

void Window::display() { _window.display(); }

void Window::clear() { _window.clear(); }

void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	_window.draw(drawable, states);
}
