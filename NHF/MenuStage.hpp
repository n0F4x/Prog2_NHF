#pragma once

#include "App.hpp"
#include "Button.hpp"


class MenuStage : public Stage {
private:
	AppData& _appData;

	Button _PlayButton;

public:
	MenuStage(AppData& appData);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;
};

