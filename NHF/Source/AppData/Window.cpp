#include "Window.hpp"


Window::Window(MenuManager& menus) : _controller{ menus }, _event{} {}

void Window::init() {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.sRgbCapable = true;

	create(sf::VideoMode::getDesktopMode(), "My Game", sf::Style::Fullscreen, settings);

	setVerticalSyncEnabled(true);
	setKeyRepeatEnabled(false);
}

bool Window::isRunning() {
	return isOpen();
}

void Window::pollEvents() {
	while (RenderWindow::pollEvent(_event)) {
		if (_event.type == sf::Event::Closed)
			close();

		_controller.handleEvent(_event);
	}
}
