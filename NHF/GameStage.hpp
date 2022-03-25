#pragma once

#include "App.hpp"
#include "Track.hpp"


class GameStage : public Stage {
private:
	AppData& _appData;

	bool _isPaused = false;

	Track _track;

public:
	GameStage(AppData& data);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;

	void pause() override;
	void resume() override;
};

