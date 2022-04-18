#include "MainMenu.hpp"

#include "../GUI/Widgets/Button.hpp"


MainMenu::MainMenu() {
	// Construct "Play" button
	Button* playButton = new Button{ "Play", _appData.assets.getFont("Dameron"), 56u, [&]() { Menu::open("Game"); } };
	playButton->center(_window.getSize());
	playButton->move(-1.f * sf::Vector2f{ 0,  playButton->getSize().y });
	addMenuItem(std::unique_ptr<Button>{playButton});

	// Construct "Options" button
	Button* optionsButton = new Button{ "Options", _appData.assets.getFont("Dameron"), 56u, [&]() { Menu::open("Options"); } };
	optionsButton->center(_window.getSize());
	optionsButton->move(sf::Vector2f{ 0, playButton->getSize().y });
	addMenuItem(std::unique_ptr<Button>{optionsButton});
}

void MainMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			Menu::close();
	}
}
