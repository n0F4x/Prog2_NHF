#include "App.hpp"


void App::init(bool renderPreview) {
	_appData.loadFromFiles();

	if (renderPreview) {
		_controller.renderPreview();
	}

	_controller.load();

	_window.open();
}

void App::run() {
	init(true);

	sf::Event event;
	while (_window.isOpen() && _controller.isActive()) {
		// Poll events
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_window.close();
			}
			_controller->handleEvent(event);
		}

		_controller->update();
		_controller->render();

		_window.lockFPS();
	}

	_appData.save();
}
