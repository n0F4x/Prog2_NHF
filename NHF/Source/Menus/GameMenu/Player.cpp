#include "Player.hpp"

#include "../../Core/Window.hpp"


PlayerSprite::PlayerSprite() : Sprite{ AppData::getTexture("Motor") } {
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	setScale(0.4f, 0.4f);
}


void Player::startJump() {
	_transition.start(sf::Vector2f{ 0.f, Window::getSize().y / 2.f - _sprite.getPosition().y } / 2.f, 600);
}


Player::Player() : MenuItem{ {&_transition} } {}


void Player::setPosition(const sf::Vector2f& feet) {
	_sprite.setInitPos(feet - _offset);
}


void Player::handleEvent(const sf::Event& event) {
	if (!isPaused()) {
		if (event.type == sf::Event::KeyPressed && event.key == _jumpKey) {
			_jumpKeyPressed = true;
		}
		else if (event.type == sf::Event::KeyReleased && event.key == _jumpKey) {
			_jumpKeyPressed = false;
		}
	}
}

void Player::update() {
	MenuItem::update();
	if (_jumpKeyPressed && !_transition.isActive()) {
		if (_resetJump) {
			_resetJump = false;
		}
		else {
			_resetJump = _transition.start(sf::Vector2f{ 0.f, Window::getSize().y / 2.f - _sprite.getPosition().y } / 2.f, 600);
		}
	}
}

void Player::init() {
	MenuItem::init();
	_sprite.init();
	_jumpKey.update();
	_jumpKeyPressed = false;
}

void Player::pause() {
	MenuItem::pause();
	_jumpKeyPressed = false;
}
