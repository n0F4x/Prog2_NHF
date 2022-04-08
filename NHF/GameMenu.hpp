#pragma once

#include "Menu.hpp"
#include "AppData.hpp"
#include "Track.hpp"


class GameMenu : public Menu {
private:
	bool _isPaused = false;

	Track _track;

public:
	GameMenu(AppData& data);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;

	void init() override;
	void pause() override;
	void resume() override;
};

