#include "GameStage.hpp"

#include "MenuStage.hpp"


GameStage::GameStage(AppData& data) :
	_appData{ data },
	_track{ data.window, data.math, sf::Vector2f{sf::Mouse::getPosition(data.window)} }
{}

void GameStage::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.stages.removeStage();

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

void GameStage::update() {
	if (!_isPaused) {
		_track.update();
	}
}

void GameStage::render() {
	_appData.window.clear();

	_appData.window.draw(_track);

	_appData.window.display();
}

void GameStage::pause() {
	_isPaused = true;
}

void GameStage::resume() {
	_track.setMouse(sf::Vector2f{ sf::Mouse::getPosition(_appData.window) });
	_isPaused = false;
}
