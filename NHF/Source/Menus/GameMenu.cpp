#include "GameMenu.hpp"

#include "GameMenu/Track.hpp"
#include "GameMenu/Player.hpp"


GameMenu::GameMenu() {
	addMenuItem(std::make_unique<Track>());

	sf::Vector2f playerPos = Window::getSize() / 2.f + sf::Vector2f{ 0.f, Window::getSize().y / 2.5f };
	addMenuItem(std::make_unique<Player>(playerPos));
}

void GameMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			close();
		}
	}
}
