#pragma once

#include "../Widget.hpp"


class Text : public Widget {
protected:
	sf::Text _text;

	bool isInside() const {
		return _text.getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition() });
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_text); }

public:
	Text(const sf::String& text, const sf::Font& fontStyle, unsigned characterSize) : _text{ text, fontStyle, characterSize } {
		setSize({ _text.getGlobalBounds().width, _text.getGlobalBounds().height });
	}
	void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position); }

	virtual void update() override {}
};
