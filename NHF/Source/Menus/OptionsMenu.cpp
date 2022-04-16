#include "OptionsMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI//Widgets/Bar.hpp"
#include "../GUI/Theme.hpp"


OptionsMenu::OptionsMenu(AppData& appData) : Menu{ appData } {
	// Construct "Options" text
	Text* text = new Text{ "OPTIONS", appData.assets.getFont("The Wireframe"), 66u };
	text->center(sf::Vector2f{ appData.window.getSize() });
	text->move({ 0, -1 * static_cast<float>(appData.window.getSize().y / 2) + text->getSize().y * 2 });
	text->setFillColor(theme::Purple);
	addMenuItem(std::unique_ptr<Text>{text});

	// Construct "Lane Count" bar
	Bar* bar = new Bar{ {"3", "4", "5", "6", "7", "8"}, appData.assets.getFont("Dameron"), 56u };
	bar->center(sf::Vector2f{ appData.window.getSize() });
	addMenuItem(std::unique_ptr<Bar>{bar});
}

void OptionsMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			_appData.menus.close();
		}
	}
}