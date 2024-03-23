#include "App.hpp"


void App::init(bool renderPreview) {
	_appData.loadAssets();

	if (renderPreview) {
		_controller.renderPreview();
	}
	_controller.load();

	_appData.loadContexts();

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
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4 && event.key.alt) {
				_window.close();
			}
			_controller->handleEvent(event);
		}

		_controller->update();
		_controller->render();

		_window.lockFPS();
	}

    _window.cleanUp();

	_appData.save();
    _appData.cleanUp();
}
