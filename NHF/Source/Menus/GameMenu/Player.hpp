#pragma once

#include "../MenuItem.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


class PlayerSprite : public sf::Sprite, public Transitionable {
private:
	sf::Vector2f _initPos;

public:
	explicit PlayerSprite(const sf::Vector2f& centerPos);

	// overriding @Transitionable
	void transition(const sf::Vector2f& amount) override { move(amount); }

	void init() { setPosition(_initPos); }
};


class Player : public MenuItem {
private:
	PlayerSprite _sprite;
	sf::Vector2f _feetPos;

	bool _jumpKeyPressed = false;

	// Transition(s)
	Transitions::Jump _transition{ &_sprite };

	// Context accessor(s)
	ContextRepr<sf::Event::KeyEvent> _jumpKey{ AppData::findContext("jumpKey") };

	// overriding @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_sprite); }

public:
	explicit Player(const sf::Vector2f& centerPos) : _sprite{ centerPos }, _feetPos{ centerPos } {
		MenuItem::addTransition(&_transition);
	}

	bool isJumping() const { return _transition.isActive(); }
	const sf::Vector2f& getFeet() const { return _feetPos; }

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
	void pause() override;
};
