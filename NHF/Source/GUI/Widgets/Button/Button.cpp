#include "Button.hpp"



bool Button::isInside(const sf::Vector2f& point) const {
	return _text.getGlobalBounds().contains(sf::Vector2f{ point });
}

void Button::triggerCallback() {
	if (_callback)
		_callback();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_text); }


using namespace btn;
Button::Button(
	AssetManager& assets,
	const sf::String& text,
	const sf::Font& fontStyle,
	unsigned characterSize,
	std::function<void()> callback
) :
	StateMachine{ /*&_states[DEFAULT] */ },
	_text{ text, fontStyle, characterSize },
	_callback{ callback }
{
	setSize({ _text.getLocalBounds().width, _text.getLocalBounds().height });

	sf::FloatRect rect = _text.getLocalBounds();
	_text.setOrigin({ rect.left + rect.width / 2.f, rect.top + rect.height / 2.f });

	//--------------------------------------StateMachine--------------------------------------
	StateMachine::init(&_states[DEFAULT]);
	_states[DEFAULT].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				assets.getSound("ButtonHover").play();
				return &_states[HOVERED];
			}
			return &_states[DEFAULT];
		}
	);

	_states[HOVERED].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (!isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				return &_states[DEFAULT];
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					assets.getSound("ButtonClick").play();
					return &_states[PRESSED];
				}
			}
			return &_states[HOVERED];
		}
	);
	_states[PRESSED].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (!isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				assets.getSound("ButtonRelease").play();
				return &_states[ACTIVE];
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					assets.getSound("ButtonRelease").play();
					triggerCallback();
					return &_states[HOVERED];
				}
			}
			return &_states[PRESSED];
		}
	);
	_states[ACTIVE].setEventListener(
		[&](const sf::Event& event) -> State* {
			if (isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				assets.getSound("ButtonClick").play();
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


void Button::center(const Window& window) { setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f }); }


void Button::update() {
	_text.setFillColor(_states[getCurrentID()]._color);
}
