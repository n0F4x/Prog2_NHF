#include "GameMenu.hpp"

#include "MainMenu.hpp"


GameMenu::GameMenu(AppData& appData) :
	Menu{ appData },
	_track{ _appData.window, _appData.engine, sf::Vector2f{sf::Mouse::getPosition(_appData.window)} }
{}

void GameMenu::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.menus.close();

		if (event.key.code == sf::Keyboard::Space)
			if (!_isPaused)
				pause();
			else
				resume();
	}

	if (!_isPaused) {
		_track.handleEvent(event);
	}
}

void GameMenu::update() {
	if (!_isPaused) {
		_track.update();
	}
}

void GameMenu::render() {
	_appData.window.clear();

	_appData.window.draw(_track);

	_appData.window.display();
}

void GameMenu::init() {
	_track.init();
	resume();
}

void GameMenu::pause() {
	_isPaused = true;
}

void GameMenu::resume() {
	_track.setMouse(sf::Vector2f{ sf::Mouse::getPosition(_appData.window) });
	_isPaused = false;
}
