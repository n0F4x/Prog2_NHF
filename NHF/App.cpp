#include "App.hpp"


void App::run() {
	_appData.init();

	while (_appData.window.isOpen() && !_appData.menus.isEmpty()) {
		_appData.window.pollEvents();
		_appData.menus.update();
		_appData.menus.render();
	}
}
