#pragma once

#include "State.hpp"


namespace btn {
	static const size_t DEFAULT = 0;
	static const size_t HOVERED = 1;
	static const size_t PRESSED = 2;
	static const size_t ACTIVE = 3;
}

class ButtonState : public State {
public:
	const sf::Color& _color;

	ButtonState(size_t id, const sf::Color& color);
};
