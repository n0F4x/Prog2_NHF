#include "App.hpp"


void App::init() {
	_appData.init();
	_window.init();
	_controller.init();
}

void App::run() {
	init();

	while (_window.isOpen() && !_controller.isEmpty()) {
		sf::Event event;
		if (_clock.getElapsedTime().asMilliseconds() >= 1000 / fps) {
			_clock.restart();

			while (_window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					_window.close();
				}
				_controller.handleEvent(event);
			}
			_controller.update();
			_controller.render();
		}
	}
}
