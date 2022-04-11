#pragma once

#include "../Widget.hpp"


class Text : public Widget {
protected:
	sf::Text _text;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_text); }

public:
	Text(const sf::String& text, const sf::Font& fontStyle, unsigned characterSize) : _text{ text, fontStyle, characterSize } {
		setSize({ _text.getLocalBounds().width, _text.getLocalBounds().height });

		sf::FloatRect rect = _text.getLocalBounds();
		_text.setOrigin({ rect.left + rect.width / 2.f, rect.top + rect.height / 2.f });
	}
	Text(const Text&) = delete;

	virtual void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position); }
	virtual void setFillColor(const sf::Color& color) { _text.setFillColor(color); }

	virtual void center(const Window& window) { setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f }); }

	virtual void update() override {}
};
