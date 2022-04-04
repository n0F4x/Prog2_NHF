#pragma once

#include "AppData.hpp"
#include "Track.hpp"


class GameMenu : public Menu {
private:
	AppData& _appData;

	bool _isPaused = false;

	Track _track;

public:
	GameMenu(AppData& data);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;

	void pause() override;
	void resume() override;
};

