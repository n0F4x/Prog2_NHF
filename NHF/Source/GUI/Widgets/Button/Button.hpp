#pragma once

#include <SFML/Audio.hpp>
#include "../../../AppData/AppData.hpp"
//#include "../Text/Text.hpp"
#include "../Widget.hpp"
#include "../../StateMachine.hpp"
#include "ButtonState.hpp"
#include "../../Theme.hpp"


class Button : public Widget, protected StateMachine {
private:
	sf::Text _text;

	ButtonState _states[4] = {
		ButtonState{btn::DEFAULT, theme::Primary},
		ButtonState{btn::HOVERED, theme::Secondary},
		ButtonState{btn::PRESSED, theme::Tertiary},
		ButtonState{btn::ACTIVE, theme::Quaternary},
	};

	std::function<void()> _callback;

	// Helpers
	bool isInside(const sf::Vector2f& point) const;
	void triggerCallback();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Button(
		AssetManager& assets,
		const sf::String& text,
		const sf::Font& fontStyle,
		unsigned characterSize,
		std::function<void()> callback
	);
	Button(const Button&) = delete;

	virtual void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position); }

	virtual void center(const Window& window) override;

	void handleEvent(const sf::Event& event) override { StateMachine::handleEvent(event); }
	void update() override;
};
