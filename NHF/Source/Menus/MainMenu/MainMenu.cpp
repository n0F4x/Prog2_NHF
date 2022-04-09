#include "MainMenu.hpp"

#include "../../GUI/Widgets/Button/Button.hpp"


MainMenu::MainMenu(AppData& appData) :
	Menu{ appData }
{
	// Construct "Play" button
	Button* playButton = new Button{ _appData.assets, "Play", _appData.assets.getFont("Dameron"), 56, [&]() { _appData.menus.open("Game"); } };
	playButton->setPosition({
		_appData.window.getSize().x / 2 - playButton->getSize().x / 2,
		_appData.window.getSize().y / 2 - playButton->getSize().y / 2
		}
	);
	addMenuItem(std::unique_ptr<Button>{playButton});
}

void MainMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.menus.close();
	}
}
