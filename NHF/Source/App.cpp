#include "App.hpp"


void App::init() {
	_window.open();
	_controller.render();

	sf::Clock clock;
	_controller.init();
	while (clock.getElapsedTime().asMilliseconds() < 2000);
}

void App::run() {
	init();

	sf::Event event;
	while (_window.isOpen() && _controller.isActive()) {
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
