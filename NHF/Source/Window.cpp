#include "Window.hpp"


sf::RenderWindow Window::_window;


void Window::init() {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.sRgbCapable = true;

	_window.create(sf::VideoMode::getDesktopMode(), "My Game", sf::Style::Fullscreen, settings);

	_window.setVerticalSyncEnabled(true);
	_window.setKeyRepeatEnabled(false);
}


sf::Vector2f Window::getSize() const {
	return sf::Vector2f{ _window.getSize() };
}

void Window::close() { _window.close(); }

bool Window::isOpen() const {
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
