#include "MainMenu.hpp"

#include "../GUI/Widgets/Button.hpp"


MainMenu::MainMenu(AppData& appData) :
	Menu{ appData }
{
	// Construct "Play" button
	Button* playButton = new Button{ "Play", _appData.assets.getFont("Dameron"), 56, [&]() { _appData.menus.open("Game"); } };
	playButton->center(sf::Vector2f{ _appData.window.getSize() });
	playButton->move(-1.f * sf::Vector2f{ 0,  playButton->getSize().y });
	addMenuItem(std::unique_ptr<Button>{playButton});

	// Construct "Options" button
	Button* optionsButton = new Button{ "Options", _appData.assets.getFont("Dameron"), 56, [&]() { _appData.menus.open("Options"); } };
	optionsButton->center(sf::Vector2f{ _appData.window.getSize() });
	optionsButton->move(sf::Vector2f{ 0,  playButton->getSize().y });
	addMenuItem(std::unique_ptr<Button>{optionsButton});
}

void MainMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.menus.close();
	}
}
