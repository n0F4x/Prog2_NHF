#include "GameMenu.hpp"

#include "GameMenu/Track.hpp"


GameMenu::GameMenu() {
	addMenuItem(std::make_unique<Track>());
}

void GameMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			Menu::close();

		if (event.key.code == sf::Keyboard::Space)
			if (!_isPaused)
				pause();
			else
				resume();
	}
}
