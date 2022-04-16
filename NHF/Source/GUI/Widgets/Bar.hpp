#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../Widget.hpp"
#include "Text.hpp"


class Bar : public Widget {
private:
	std::vector<Text> _contents;

	std::vector<sf::RectangleShape> _cells;

	size_t _selected = 0;
	sf::RectangleShape _emphasis;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Bar(float width, const std::vector<std::string>& contents, const sf::Font& font, unsigned characterSize);

	virtual void setPosition(const sf::Vector2f& position) override;

	virtual void center(const sf::Vector2f& window) override;
	virtual void move(const sf::Vector2f& amount) override;

	virtual void handleEvent(const sf::Event& event) override;
};