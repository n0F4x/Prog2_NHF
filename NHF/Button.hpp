#pragma once

#include <SFML/Audio.hpp>
#include "AppData.hpp"
#include "Text.hpp"
#include "StateMachine.hpp"
#include "ButtonState.hpp"
#include "Theme.hpp"


class Button : public Text, protected StateMachine {
private:
	AssetManager& _assets;

	ButtonState _states[4] = {
		ButtonState{btn::DEFAULT, theme::Primary},
		ButtonState{btn::HOVERED, theme::Secondary},
		ButtonState{btn::PRESSED, theme::Tertiary},
		ButtonState{btn::ACTIVE, theme::Quaternary},
	};

	std::function<void()> _callback;

	void triggerCallback();

public:
	Button(
		AssetManager& assets,
		const sf::String& text,
		const sf::Font& fontStyle,
		unsigned characterSize,
		std::function<void()> callback
	);

	void handleEvent(const sf::Event& event) override { StateMachine::handleEvent(event); }
	void update() override;
};
