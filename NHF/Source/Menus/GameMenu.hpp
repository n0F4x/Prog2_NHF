#pragma once

#include "Menu.hpp"
#include "GameMenu/Track.hpp"
#include "GameMenu/Player.hpp"
#include "GameMenu/PauseScreen.hpp"


/**
 * @brief	Class for managing and displaying the game menu of the application
*/
class GameMenu : public Menu {
private:
	Track _track;
	Player _player;
	sf::CircleShape _playerCircle;
	PauseScreen _pauseScreen{ [this]() {resume(); }, [this]() {close(); pause(); }, [this]() {init();} };

	bool _gameOver = false;

public:
	/**
	 * @brief	Constructs a new GameMenu
	*/
	GameMenu();

	/**
	 * @brief	Handles user input inside the game menu
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Updates the states of the menu
	*/
	void update() override;
	/**
	 * @brief	Renders the contents of the menu to the screen
	*/
	void render() override;
	/**
	 * @brief	Initializes the states of the menu
	*/
	void init() override;
	/**
	 * @brief	Pauses the menu's states
	*/
	void pause() override;
	/**
	 * @brief	Resumes the menu's states
	*/
	void resume() override;
};
