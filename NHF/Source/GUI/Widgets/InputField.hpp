#pragma once

#include <functional>
#include <string>
#include "../Widget.hpp"
#include "Text.hpp"


/**
 * @brief	Class that acts as an input field widget. Utilizes the context system under the hood
*/
class InputField : public Widget {
private:
	ContextRepr<sf::Event::KeyEvent> _context;

	Text _text;
	std::string _string;
	sf::RectangleShape _frame;

	sf::Clock _clock;
	void setActive(bool isActive);
	std::string _activeString;
	bool _isActive = false;

	/**
	 * @brief	Draws input field to the render target
	 * @param target	Render target
	 * @param states	Render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	/**
	 * @brief	Constructs a new InputField
	 * @param fontStyle	The style of the text displayed inside the input field
	 * @param characterSize	The character size of the text
	 * @param contextName	The name of the context that the class is hooked to
	*/
	InputField(
		const sf::Font& fontStyle,
		unsigned characterSize,
		const std::string_view& contextName
	);

	/**
	 * @brief	Setter for the input field's position
	 * @param position	New position
	*/
	void setPosition(const sf::Vector2f& position) override;

	/**
	 * @brief	Handles user input
	 * @param event	User input
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Updates the input field
	*/
	void update() override;
	/**
	 * @brief	Initializes the input field
	*/
	void init() override;
};