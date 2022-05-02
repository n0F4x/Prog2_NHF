#include "App.hpp"


void App::init() {
	_window.open();
	_controller.render();

	_controller.init();
}

void App::run() {
	init();
}

bool App::isRunning() { return _window.isOpen() && _controller.isActive(); }

void App::handleEvent(const sf::Event& event) const {
	if (event.type == sf::Event::Closed) {
		_window.close();
	}
	_controller.handleEvent(event);
	_controller.update();
	_controller.render();
}
