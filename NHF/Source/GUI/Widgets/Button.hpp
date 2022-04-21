#pragma once

#include <functional>
#include "../Widget.hpp"
#include "Text.hpp"


class Button : public Widget {
private:
	Text _text;
	std::function<void()> _callback;

	// Helpers
	bool isInside(const sf::Vector2f& point) const;
	void triggerCallback();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Button(
		const sf::String& text,
		const sf::Font& fontStyle,
		unsigned characterSize,
		std::function<void()> callback
	);
	Button(const Button&) = delete;

	void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.center(getLocalBounds()); }

	void handleEvent(const sf::Event& event) override;
	void resume() override;
};
