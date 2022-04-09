#include "Button.hpp"

using namespace btn;


void Button::triggerCallback() {
	if (_callback)
		_callback();
}


Button::Button(
	AssetManager& assets,
	const sf::String& text,
	const sf::Font& fontStyle,
	unsigned characterSize,
	std::function<void()> callback
) :
	Text{ text, fontStyle, characterSize },
	StateMachine{ /*&_states[DEFAULT] */},
	_assets{ assets },
	_callback{ callback }
{
	StateMachine::init(&_states[DEFAULT]);
	_states[DEFAULT].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (isInside()) {
				_assets.getSound("ButtonHover").play();
				return &_states[HOVERED];
			}
			return &_states[DEFAULT];
		}
	);

	_states[HOVERED].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (!isInside()) {
				return &_states[DEFAULT];
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_assets.getSound("ButtonClick").play();
					return &_states[PRESSED];
				}
			}
			return &_states[HOVERED];
		}
	);
	_states[PRESSED].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (!isInside()) {
				_assets.getSound("ButtonRelease").play();
				return &_states[ACTIVE];
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_assets.getSound("ButtonRelease").play();
					triggerCallback();
					return &_states[HOVERED];
				}
			}
			return &_states[PRESSED];
		}
	);
	_states[ACTIVE].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (isInside()) {
				_assets.getSound("ButtonClick").play();
				return &_states[PRESSED];
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					return &_states[DEFAULT];
				}
			}
			return &_states[ACTIVE];
		}
	);
}

void Button::update() {
	_text.setFillColor(_states[getCurrentID()]._color);
}
