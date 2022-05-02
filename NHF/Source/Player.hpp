#pragma once

#include "MenuItem.hpp"
#include "Transitions.hpp"
#include "Transitionable.hpp"
#include "AppData.hpp"

namespace sf { 
	class Sprite {
	public:
		void setPosition(const sf::Vector2f&) const { /*Removed visuals*/ }
		void move(const sf::Vector2f&) const { /*Removed visuals*/ }
		

		virtual ~Sprite() = default;
	};
}


class PlayerSprite : public sf::Sprite, public Transitionable {
private:
	sf::Vector2f _initPos;

public:
	explicit PlayerSprite(const sf::Vector2f& feetCoords);

	// overriding @Transitionable
	void transition(const sf::Vector2f& amount) override { move(amount); }

	void init() const { setPosition(_initPos); }
};


class Player : public MenuItem {
private:
	PlayerSprite _sprite;
	sf::Vector2f _feetPos;

	// Transition(s)
	Transitions::Jump _transition{&_sprite};

	// overriding @MenuItem
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override { /*Removed visuals*/ }

public:
	explicit Player(const sf::Vector2f& feetPos) : _sprite{ feetPos } {}

	bool isJumping() const { return _transition.isActive(); }
	const sf::Vector2f& getFeet() const { return _feetPos; }

	void handleEvent(const sf::Event& event) override;
	void init() override { MenuItem::init(); _sprite.init(); }
};