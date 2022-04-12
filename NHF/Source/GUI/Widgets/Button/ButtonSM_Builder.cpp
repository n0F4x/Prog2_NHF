#include "ButtonSM_Builder.hpp"

#include "Button.hpp"
#include "../../../GUI/Theme.hpp"


// State names / IDs
static const size_t DEFAULT = 0;
static const size_t HOVERED = 1;
static const size_t PRESSED = 2;
static const size_t ACTIVE = 3;


void ButtonSM_Builder::buildStates(StateMachine& SM) const {
	SM_Builder::addState(SM, std::make_unique<State>(DEFAULT, ButtonStateData{theme::Primary}));
	SM_Builder::addState(SM, std::make_unique<State>(HOVERED, ButtonStateData{theme::Secondary}));
	SM_Builder::addState(SM, std::make_unique<State>(PRESSED, ButtonStateData{theme::Tertiary}));
	SM_Builder::addState(SM, std::make_unique<State>(ACTIVE, ButtonStateData{theme::Quaternary}));
}

void ButtonSM_Builder::buildTransitions(StateMachine& SM) const {
	SM_Builder::getState(SM, DEFAULT)->setEventListener(
		[&](const sf::Event& event) -> size_t {
			if (_button.isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				//_assets.getSound("ButtonHover").play();
				return HOVERED;
			}
			return DEFAULT;
		}
	);

	SM_Builder::getState(SM, HOVERED)->setEventListener(
		[&](const sf::Event& event) -> size_t {
			if (!_button.isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				return DEFAULT;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					//_assets.getSound("ButtonClick").play();
					return PRESSED;
				}
			}
			return HOVERED;
		}
	);

	SM_Builder::getState(SM, PRESSED)->setEventListener(
		[&](const sf::Event& event) -> size_t {
			if (!_button.isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				//_assets.getSound("ButtonRelease").play();
				return ACTIVE;
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					//_assets.getSound("ButtonRelease").play();
					_button.triggerCallback();
					return HOVERED;
				}
			}
			return PRESSED;
		}
	);

	SM_Builder::getState(SM, ACTIVE)->setEventListener(
		[&](const sf::Event& event) -> size_t {
			if (_button.isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
				//_assets.getSound("ButtonClick").play();
				return PRESSED;
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					return DEFAULT;
				}
			}
			return ACTIVE;
		}
	);
}
