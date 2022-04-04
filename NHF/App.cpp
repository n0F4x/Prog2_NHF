#include "App.hpp"

#include "InitMenu.hpp"
#include "MainMenu.hpp"


App::App() {
	_appData.menus.addMenu(std::make_unique<InitMenu>(_appData));
	_appData.menus.processChanges();
	_appData.menus.current().render();

	_appData.engine.init();

	_appData.menus.addMenu(std::make_unique<MainMenu>(_appData));
	_appData.menus.processChanges();
}

void App::run() {
	sf::Event event;

	while (_appData.window.isOpen() && !_appData.menus.isEmpty()) {
		while (_appData.window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				_appData.window.close();

			_appData.menus.current().handleEvent(event);
		}

		_appData.menus.current().update();
		_appData.menus.current().render();

		_appData.menus.processChanges();
	}
}
