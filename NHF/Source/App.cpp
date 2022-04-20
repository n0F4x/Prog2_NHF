#include "App.hpp"


void App::init() {
	AppData::init();
	Window::init();
	_controller.init();
}

void App::run() {
	init();

	while (Window::isOpen() && !_controller.isEmpty()) {
		sf::Event event;
		if (_clock.getElapsedTime().asMilliseconds() >= 1000 / fps) {
			_clock.restart();

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
}
