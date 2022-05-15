#pragma once

#include <SFML/Graphics.hpp>
#include "../Menus/MenuItem.hpp"


/**
 * @brief Abstract class for implementing widgets
*/
class Widget : public MenuItem {
private:
	sf::Vector2f _position;
	sf::Vector2f _size;

protected:
	/**
	 * @brief	Sets the size of the widget
	 * @param size	The new size
	*/
	void setSize(const sf::Vector2f& size) { _size = size; }

public:
	/**
	 * @brief	Constructs a new Widget
	 * @param position	The position of the new widget
	 * @param size	The size of the new widget
	*/
	Widget(const sf::Vector2f& position = { 0, 0 }, const sf::Vector2f& size = { 0, 0 }) : _position{ position }, _size{ size } {}
	/**
	 * @brief	Copy constructor
	*/
	Widget(const Widget& other) = default;
	
	/**
	 * @brief	Sets the position of the widget
	 * @param position	The new position
	*/
	virtual void setPosition(const sf::Vector2f& position) { _position = position; }
	/**
	 * @brief	Gets the position of the widget
	 * @return	The position of the widget
	*/
	const sf::Vector2f& getPosition() const { return _position; }
	/**
	 * @brief	Gets the size of the widget
	 * @return	The size of the widget
	*/
	const sf::Vector2f& getSize() const { return _size; }
	/**
	 * @brief	Gets the bounds of the widget
	 * @return	The bounds of the widget
	*/
	sf::FloatRect getLocalBounds() const { return sf::FloatRect{ _position.x, _position.y, _size.x, _size.y }; }

	/**
	 * @brief	Centers the widget in the frame given as parameter
	 * @param frame	A frame where the widget will be centered
	*/
	virtual void center(const sf::FloatRect& frame) { setPosition({ frame.left + frame.width / 2 - getSize().x / 2, frame.top + frame.height / 2 - getSize().y / 2 }); }
	/**
	 * @brief	Moves the widget by an given as parameter amount
	 * @param amount	The amount that the widget will move
	*/
	virtual void move(const sf::Vector2f& amount) { setPosition(_position + amount); }
};

