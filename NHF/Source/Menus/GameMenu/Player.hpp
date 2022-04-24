#pragma once

#include "../MenuItem.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


class Player : public MenuItem, public Transitionable {
private:
	sf::Sprite _sprite;
	sf::Vector2f _feetCoords;

	Transitions::Jump _transition{this};

	// overriding @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { /*TODO*/ }
	// overriding @Transitionable
	void transition(const sf::Vector2f amount) override {/*TODO*/ }

public:
	Player();

	bool isJumping() const { return _transition.isActive(); }
	sf::Vector2f getFeet() const { _sprite.getPosition() + _feetCoords; }

	void handleEvent(const sf::Event& event) override { /*TODO*/ }
	void update() override { /*TODO*/ }
	void init() override { /*TODO*/ }
};