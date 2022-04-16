#pragma once

#include <functional>
#include "../Widget.hpp"


class Button : public Widget {
private:
	sf::Text _text;
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

	virtual void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position); }

	virtual void center(const sf::Vector2f& window) override { setPosition({ window.x / 2.f, window.y / 2.f }); }
	virtual void move(const sf::Vector2f& amount) override { Widget::move(amount); _text.move(amount); }

	void handleEvent(const sf::Event& event) override;
};
