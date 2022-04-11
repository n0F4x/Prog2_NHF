#include "OptionsMenu.hpp"

#include "../../GUI/Widgets/Text/Text.hpp"


OptionsMenu::OptionsMenu(AppData& appData) : Menu{ appData } {
	Text* text = new Text{ "OPTIONS", appData.assets.getFont("The Wireframe"), 200 };
	text->center(_appData.window);
	addMenuItem(std::unique_ptr<Text>{text});
}

void OptionsMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			_appData.menus.close();
		}
	}
}