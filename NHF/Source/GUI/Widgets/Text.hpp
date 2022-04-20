#pragma once

#include "../Widget.hpp"


class Text : public Widget {
protected:
	sf::Text _text;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_text); }

public:
	Text() = default;
	Text(const sf::String& text, const sf::Font& fontStyle, unsigned characterSize);
	Text(const Text&) = default;

	void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position); }
	void setFillColor(const sf::Color& color) { _text.setFillColor(color); }
	void setString(const sf::String& string);
	const sf::String& getString() const { return _text.getString(); }

	void center(const sf::Vector2f& window) override { setPosition({ window.x / 2.f, window.y / 2.f }); }
	void move(const sf::Vector2f& amount) override { Widget::move(amount); _text.move(amount); }

	void update() override {}
};
