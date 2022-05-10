#pragma once

#include "../MenuItem.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


class PlayerSprite : public sf::Sprite, public Transitionable {
private:
	sf::Vector2f _initPos;

public:
	PlayerSprite();

	void setInitPos(const sf::Vector2f& pos) { _initPos = pos; setPosition(pos); }
	const sf::Vector2f& getInitPos() const { return _initPos; }

	// overriding @Transitionable
	void transition(const sf::Vector2f& amount) override { move(amount); }

	void init() { setPosition(_initPos); }
};


class Player : public MenuItem {
private:
	PlayerSprite _sprite;
	sf::Vector2f _offset = { 0.f, 35.f };

	bool _jumpKeyPressed = false;
	bool _resetJump = false;

	// Transition(s)
	Transitions::Jump _transition{ &_sprite };

	// Context accessor(s)
	ContextRepr<sf::Event::KeyEvent> _jumpKey{ AppData::findContext("jumpKey") };

	// overriding @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_sprite); }

public:
	Player() : MenuItem{ {&_transition} } {}

	bool isJumping() const { return _transition.isActive(); }
	sf::Vector2f getFeet() const { return _sprite.getInitPos() + _offset; }
	void setFeet(const sf::Vector2f& feet);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
	void pause() override;
};
