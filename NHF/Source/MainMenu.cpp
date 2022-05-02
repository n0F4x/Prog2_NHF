#include "MainMenu.hpp"


void MainMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Num1) {
			Menu::open("Game");
		}
		if (event.key.code == sf::Keyboard::Num2) {
			Menu::open("Options");
		}
	}
}
