#pragma once

#include <SFML/Graphics.hpp>
#include "../Menus/MenuItem.hpp"


class Widget : public MenuItem {
private:
	sf::Vector2f _position;
	sf::Vector2f _size;

protected:
	void setSize(const sf::Vector2f& size) { _size = size; }

public:
	Widget(const sf::Vector2f& position = { 0, 0 }, const sf::Vector2f& size = { 0, 0 }) : _position{ position }, _size{ size } {}
	Widget(const Widget& other) = default;

	virtual void setPosition(const sf::Vector2f& position) { _position = position; }
	const sf::Vector2f& getPosition() const { return _position; }
	const sf::Vector2f& getSize() const { return _size; }
	sf::FloatRect getLocalBounds() const { return sf::FloatRect{ _position.x, _position.y, _size.x, _size.y }; }

	virtual void center(const sf::FloatRect& frame) { setPosition({ frame.left + frame.width / 2 - getSize().x / 2, frame.top + frame.height / 2 - getSize().y / 2 }); }
	virtual void move(const sf::Vector2f& amount) { setPosition(_position + amount); }
};

