#include "MainMenu.hpp"

#include "../../GUI/Widgets/Button/Button.hpp"


MainMenu::MainMenu(AppData& appData) :
	Menu{ appData }
{
	// Construct "Play" button
	Button* playButton = new Button{ _appData.assets, "Play", _appData.assets.getFont("Dameron"), 56, [&]() { _appData.menus.open("Game"); } };
	playButton->center(_appData.window);
	addMenuItem(std::unique_ptr<Button>{playButton});
}

void MainMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.menus.close();
	}
}
