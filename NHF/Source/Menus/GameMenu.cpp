#include "GameMenu.hpp"

#include "../Utilities/Math.hpp"
#include "../GUI/Theme.hpp"


GameMenu::GameMenu() {
	sf::Vector2f playerPos = Window::getSize() / 2.f + sf::Vector2f{ 0.f, Window::getSize().y / 2.5f };
	_player.setFeet(playerPos);

	_playerCircle.setRadius(math::calcDistance(_player.getFeet(), Window::getSize() / 2.f));
	_playerCircle.setOrigin(_playerCircle.getRadius(), _playerCircle.getRadius());
	_playerCircle.setPosition(Window::getSize() / 2.f);
	_playerCircle.setPointCount(100);
	_playerCircle.setFillColor(sf::Color::Transparent);
	_playerCircle.setOutlineThickness(1.f);
	_playerCircle.setOutlineColor(theme::NeonYellow);
}

void GameMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (!_gameOver) {
		_track.handleEvent(event);
		_player.handleEvent(event);
	}
	_pauseScreen.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		if (!isPaused()) {
			pause();
		}
		else {
			resume();
		}
	}

	if (_gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
		init();
	}
}

void GameMenu::update() {
	if (!_gameOver) {
		_track.update();
		_player.update();
	}
	_pauseScreen.update();

	if (!_gameOver && !_player.isJumping() && !_track.isOnPlatforms(_player.getFeet())) {
		_gameOver = true;
		_pauseScreen.gameOver();
		pause();
	}
}

void GameMenu::render() {
	Window::clear();

	Window::draw(_track);
	Window::draw(_playerCircle);
	Window::draw(_player);
	Window::draw(_pauseScreen);

	Window::display();
}

void GameMenu::init() {
	Menu::init();
	_track.init();
	_player.init();
	_pauseScreen.init();
	_gameOver = false;
}

void GameMenu::pause() {
	Menu::pause();
	if (!_gameOver) {
		_track.pause();
		_player.pause();
	}
	_pauseScreen.pause();
}

void GameMenu::resume() {
	Menu::resume();
	if (!_gameOver) {
		_track.resume();
		_player.resume();
	}
	_pauseScreen.resume();
}
