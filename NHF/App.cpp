#include "App.hpp"

#include "MenuStage.hpp"


App::App() {
	_appData.stages.addStage(std::make_unique<MenuStage>( _appData ));
	_appData.stages.processChanges();
}

void App::run() {
	sf::Event event;

	while (_appData.window.isOpen() && !_appData.stages.isEmpty()) {
		while (_appData.window.pollEvent(event)) {
 			_appData.stages.current().handleEvent(event);

			if (event.type == sf::Event::Closed)
				_appData.window.close();
		}

		_appData.stages.current().update();
		_appData.stages.current().render();

		_appData.stages.processChanges();
	}
}
