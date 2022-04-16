#include "InitMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI/Theme.hpp"


InitMenu::InitMenu(AppData& appData) : Menu{ appData } {
	// Construct title
	Text* title = new Text{ "PLATFORMS", _appData.assets.getFont("The Wireframe"), 165u };
	title->center(sf::Vector2f{ _appData.window.getSize() });
	title->setFillColor(theme::Purple);
	addMenuItem(std::unique_ptr<Text>(title));
}

void InitMenu::update() {}
