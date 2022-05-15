#pragma once

#include "../MenuItem.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


/**
 * @brief	Class for managing the sprite of the Player class
*/
class PlayerSprite : public sf::Sprite, public Transitionable {
private:
	sf::Vector2f _initPos;

public:
	/**
	 * @brief	Constructs a new PlayerSprite, setting its initial position to {0,0}
	*/
	PlayerSprite();

	/**
	 * @brief	Sets the initial position of the player
	 * @param pos	The initial position
	*/
	void setInitPos(const sf::Vector2f& pos) { _initPos = pos; setPosition(pos); }
	/**
	 * @brief	Gets the initial position of the player
	 * @return	The initial position of the player
	*/
	const sf::Vector2f& getInitPos() const { return _initPos; }

	/**
	 * @brief	Moves the sprite by a given amount
	 * @param amount	The given amount
	*/
	void transition(const sf::Vector2f& amount) override { move(amount); }

	/**
	 * @brief	Resets the sprite's position to its initial position
	*/
	void init() { setPosition(_initPos); }
};


/**
 * @brief	Class that acts as a player inside the game
*/
class Player : public MenuItem {
private:
	PlayerSprite _sprite;
	const sf::Vector2f _offset = { 0.f, 30.f };

	bool _jumpKeyPressed = false;
	bool _resetJump = false;

	// Transition(s)
	Transitions::Jump _transition{ &_sprite };

	// Context accessor(s)
	ContextRepr<sf::Event::KeyEvent> _jumpKey{ AppData::findContext("jumpKey") };

protected:
	/**
	 * @brief	Starts the jumping process of the player
	*/
	void startJump();
	/**
	 * @brief	Draws the player to the render target
	 * @param target	The render target
	 * @param states	The render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_sprite); }

public:
	/**
	 * @brief	Constructs a new player
	*/
	Player();

	/**
	 * @brief	Checks whether the player is in a jumping state
	 * @return	True if the player is currently jumping
	*/
	bool isJumping() const { return _transition.isActive(); }
	/**
	 * @brief	Gets the coordinates of the player's feet
	 * @return	The coordinate of the player's feet
	*/
	sf::Vector2f getFeet() const { return _sprite.getInitPos() + _offset; }
	/**
	 * @brief	Sets the player's position
	 * @param feet	The new coordinates of the player's feet
	*/
	void setPosition(const sf::Vector2f& feet);

	/**
	 * @brief	Handles user input
	 * @param event	The user input
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Updates the state of the player
	*/
	void update() override;
	/**
	 * @brief	Initializes the Player class
	*/
	void init() override;
	/**
	 * @brief	Sets the player's state to paused
	*/
	void pause() override;
};
