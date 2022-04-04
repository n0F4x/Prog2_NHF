#pragma once

#include <SFML/Audio.hpp>
#include "AppData.hpp"
#include "Widget.hpp"
#include "StateMachine.hpp"
#include "ButtonState.hpp"
#include "Theme.hpp"


class Button : public Widget, public StateMachine {
private:
	AssetManager& _assets;

	ButtonState _states[4] = {
		{btn::DEFAULT, theme::Primary},
		{btn::HOVERED, theme::Secondary},
		{btn::PRESSED, theme::Tertiary},
		{btn::ACTIVE, theme::Quaternary},
	};

	sf::Text _text;
	std::function<void()> _callback;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//Helpers
	void triggerCallback();
	bool isInside() const;

public:
	Button(
		AssetManager& assets,
		const sf::String& text,
		unsigned characterSize,
		const sf::Font& fontStyle,
		std::function<void()> callback
	);

	void update() override;

	const sf::Vector2f& getSize() const;
	void setPosition(const sf::Vector2f& position);
};
