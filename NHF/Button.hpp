#pragma once

#include "Widget.hpp"
#include "StateMachine.hpp"
#include "ButtonState.hpp"
#include "Theme.hpp"


class Button : public Widget, public StateMachine {
private:
	ButtonState _states[4] = {
		{btn::DEFAULT, sf::Color::Red},
		{btn::HOVERED, sf::Color::Blue},
		{btn::PRESSED, sf::Color::Green},
		{btn::ACTIVE, sf::Color::Yellow},
	};

	sf::Text _text;
	std::function<void()> _callback;
	void triggerCallback();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//Helpers
	bool isInside() const;

public:
	Button(
		const sf::String& text,
		unsigned characterSize,
		const sf::Font& fontStyle,
		std::function<void()> callback
	);

	void update() override;

	const sf::Vector2f& getSize() const;
	void setPosition(const sf::Vector2f& position);
};
