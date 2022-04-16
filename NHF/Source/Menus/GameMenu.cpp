#include "GameMenu.hpp"


GameMenu::GameMenu(AppData& appData) :
	Menu{ appData }
{
	addMenuItem(std::make_unique<Track>(_appData.window));
}

void GameMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.menus.close();

		if (event.key.code == sf::Keyboard::Space)
			if (!_isPaused)
				pause();
			else
				resume();
	}
}
