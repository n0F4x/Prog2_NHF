#include "Player.hpp"

#include "../../Core/Window.hpp"


PlayerSprite::PlayerSprite(const sf::Vector2f&) { /*TODO*/ }

void Player::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key == _jumpKey) {
		_transition.start({ 0.f, Window::getSize().y / 2.f - _feetPos.y + _sprite.getLocalBounds().height }, 1000);
	}
}
