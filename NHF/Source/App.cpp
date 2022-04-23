#include "App.hpp"

#include "AppData.hpp"
#include "Window.hpp"


void App::init() {
	AppData::init();
	Window::init();

	_controller.construct();
	_controller.render();

	sf::Clock clock;
	_controller.init();
	while (clock.getElapsedTime().asMilliseconds() < 2000);
}

void App::run() {
	init();

	sf::Event event;
	while (Window::isOpen() && _controller.isActive()) {
		while (Window::pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				Window::close();
			}
			_controller.handleEvent(event);
		}
		_controller.update();
		_controller.render();
	}
}
