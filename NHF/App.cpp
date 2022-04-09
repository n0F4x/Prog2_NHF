#include "App.hpp"


void App::run() {
	_appData.init();

	while (_appData.window.isOpen() && !_appData.menus.isEmpty()) {
		if (_clock.getElapsedTime().asMilliseconds() >= 1000 / fps) {
			_clock.restart();

			_appData.window.pollEvents();
			_appData.menus.update();
			_appData.menus.render();
		}
	}
}
