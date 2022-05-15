#pragma once

#include <functional>
#include "../Widget.hpp"
#include "Text.hpp"


/**
 * @brief	Class that acts as a button widget
*/
class Button : public Widget {
private:
	Text _text;
	std::function<void()> _callback;

	/**
	 * @brief	Check whether the point is inside the area of the buttons rectange
	 * @param point	Point to check, whether it is inside or not
	 * @return	True if it is inside
	*/
	bool isInside(const sf::Vector2f& point) const;
	/**
	 * @brief	Calls callback function of the button
	*/
	void triggerCallback() const;

	/**
	 * @brief	Draws button to the render target
	 * @param target	Render target
	 * @param states	Render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	/**
	 * @brief	Constructs a new Button
	 * @param text	The text on the button
	 * @param fontStyle	The font style of the text
	 * @param characterSize	The character size of the text
	 * @param callback	Callback function to be triggered when the button is pressed
	*/
	Button(
		const sf::String& text,
		const sf::Font& fontStyle,
		unsigned characterSize,
		const std::function<void()>& callback = nullptr
	);

	/**
	 * @brief	Setter for the buttons position
	 * @param position	The new position
	*/
	void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.center(getLocalBounds()); }

	/**
	 * @brief	Handles user input
	 * @param event	User input
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Resets the fill color of the button's text
	*/
	void resume() override;
};
