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
	virtual void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position); }

	virtual void center(const Window& window) override { setPosition({ window.getSize().x / 2 - getSize().x / 2, window.getSize().y / 2 - getSize().y / 2 }); }
	virtual void setFillColor(const sf::Color& color) { _text.setFillColor(color); }

	virtual void update() override {}
};
