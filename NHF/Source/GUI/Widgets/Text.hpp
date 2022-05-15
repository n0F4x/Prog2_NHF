#pragma once

#include "../Widget.hpp"


/**
 * @brief	Class that acts as a text widget
*/
class Text : public Widget {
private:
	sf::Text _text;

	/**
	 * @brief	Draws the text to the render target
	 * @param target	Render target
	 * @param states	Render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_text); }

public:
	/**
	 * @brief	Constructs an empty text
	*/
	Text() = default;
	/**
	 * @brief	Constructs a new text
	 * @param text	Message that the class is going to display
	 * @param fontStyle	Font style of the text
	 * @param characterSize	Character size of the text
	*/
	Text(const sf::String& text, const sf::Font& fontStyle, unsigned characterSize);
	/**
	 * @brief	Copy constructor of the class
	*/
	Text(const Text&) = default;

	/**
	 * @brief	Sets the position of the text
	 * @param position	The new position
	*/
	void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position + getSize() / 2.f); }
	/**
	 * @brief	Sets the fill color of the text
	 * @param color	The new fill color
	*/
	void setFillColor(const sf::Color& color) { _text.setFillColor(color); }
	/**
	 * @brief	Sets the displayed message
	 * @param string	The new message
	*/
	void setString(const sf::String& string);
	/**
	 * @brief	Gets the displayed message
	 * @return	The displayed message
	*/
	const sf::String& getString() const { return _text.getString(); }
};
