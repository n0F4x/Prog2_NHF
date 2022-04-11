#pragma once

#include <SFML/Graphics.hpp>
#include "../../Menus/MenuItem.hpp"
#include "../../AppData/Window.hpp"


class Widget : public MenuItem {
protected:
	sf::Vector2f _position;
	sf::Vector2f _size;

	void setSize(const sf::Vector2f& size) { _size = size; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

public:
	Widget(const sf::Vector2f& position = { 0, 0 }, const sf::Vector2f& size = { 0, 0 }) : _position{ position }, _size{ size } {}

	virtual void setPosition(const sf::Vector2f& position) { _position = position; }
	const sf::Vector2f& getSize() const { return _size; }

	virtual void center(const Window& window) {
		setPosition({ window.getSize().x / 2 - getSize().x / 2, window.getSize().y / 2 - getSize().y / 2 });
	}

	virtual void update() override {}
};

