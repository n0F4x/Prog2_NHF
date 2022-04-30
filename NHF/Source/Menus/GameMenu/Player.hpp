#pragma once

#include "../MenuItem.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "../../Utilities/Math/Transitionable.hpp"
#include "../../AppData.hpp"


class PlayerSprite : public sf::Sprite, public Transitionable {
private:
	sf::Vector2f _initPos;

public:
	explicit PlayerSprite(const sf::Vector2f& feetCoords);

	// overriding @Transitionable
	void transition(const sf::Vector2f& amount) override { move(amount); }

	void init() { setPosition(_initPos); }
};


class Player : public MenuItem {
private:
	PlayerSprite _sprite;
	sf::Vector2f _feetPos;

	// Transition(s)
	Transitions::Jump _transition{&_sprite};

	// Context accessor(s)
	Context::Accessor _jumpKey = AppData::context.getContext("jumpKey");

	// overriding @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_sprite); }

public:
	explicit Player(const sf::Vector2f& feetPos) : _sprite{ feetPos } {}

	bool isJumping() const { return _transition.isActive(); }
	const sf::Vector2f& getFeet() const { return _feetPos; }

	void handleEvent(const sf::Event& event) override;
	void init() override { MenuItem::init(); _sprite.init(); }
};