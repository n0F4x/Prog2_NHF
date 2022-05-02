#include "OptionsMenu.hpp"


void OptionsMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		Menu::close();
	}
}
