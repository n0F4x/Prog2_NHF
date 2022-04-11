#include "InitMenu.hpp"

#include "../../GUI/Widgets/Text/Text.hpp"


InitMenu::InitMenu(AppData& appData) : Menu{ appData } {
	// Construct title
	Text* title = new Text{ "PLATFORMS", _appData.assets.getFont("The Wireframe"), 165 };
	title->center(_appData.window);
	title->setFillColor(sf::Color::Green);
	addMenuItem(std::unique_ptr<Text>(title));
}
