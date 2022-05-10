#pragma once

#include "Menu.hpp"
#include "GameMenu/Track.hpp"
#include "GameMenu/Player.hpp"
#include "GameMenu/PauseScreen.hpp"


class GameMenu : public Menu {
private:
	Track _track;
	Player _player;
	sf::CircleShape _playerCircle;
	PauseScreen _pauseScreen{ [this]() {resume(); }, [this]() {close(); pause(); }, [this]() {init();} };

	bool _gameOver = false;

public:
	GameMenu();

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;
	void init() override;
	void pause() override;
	void resume() override;
};

