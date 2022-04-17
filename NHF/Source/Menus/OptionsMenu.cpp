#include "OptionsMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI//Widgets/Bar.hpp"
#include "../GUI/Theme.hpp"


OptionsMenu::OptionsMenu(AppData& appData) : Menu{ appData } {
	// Construct "Options" text
	Text* text = new Text{ "OPTIONS", appData.assets.getFont("The Wireframe"), 66u };
	text->center(sf::Vector2f{ appData.window.getSize() });
	text->move({ 0.f, -1.f * static_cast<float>(appData.window.getSize().y / 2u) + text->getSize().y * 2.f });
	text->setFillColor(theme::Purple);
	addMenuItem(std::unique_ptr<Text>{text});

	// Construct "Lane Count" bar and label
	Bar* LCbar = new Bar{ static_cast<float>(appData.window.getSize().x) * 0.6f, {"3", "4", "5", "6", "7", "8"}, appData.assets.getFont("Dameron"), 56u };
	LCbar->center(sf::Vector2f{ appData.window.getSize() });
	LCbar->move({ -1.f * static_cast<float>(appData.window.getSize().x) / 2.f, 0.f });
	LCbar->move({ static_cast<float>(appData.window.getSize().x) * 2.f / 3.f, 0.f });
	LCbar->setFillcolor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Bar>{LCbar});
	Text* LClabel = new Text{ "Lane Count:", appData.assets.getFont("Dameron"), 56u };
	LClabel->center(sf::Vector2f{ appData.window.getSize() });
	LClabel->move({ -1.f * sf::Vector2f(appData.window.getSize()).x / 2.f + LClabel->getSize().x / 2.f + static_cast<float>(appData.window.getSize().x) / 40.f, 0.f });
	LClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(LClabel));
}

void OptionsMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			_appData.menus.close();
		}
	}
}