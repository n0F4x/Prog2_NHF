#pragma once

#include "../Menu.hpp"
#include "../../AppData/AppData.hpp"
#include "Track.hpp"


class GameMenu : public Menu {
public:
	GameMenu(AppData& data);

	void handleEvent(const sf::Event& event) override;
};

