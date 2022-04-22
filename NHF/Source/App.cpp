#include "App.hpp"


void App::init() {
	AppData::init();
	Window::init();
	_controller.init();
}

void App::run() {
	init();

	sf::Event event;
	while (Window::isOpen() && !_controller.isEmpty()) {
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
