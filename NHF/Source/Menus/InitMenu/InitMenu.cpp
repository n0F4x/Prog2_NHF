#include "InitMenu.hpp"

#include "../../GUI/Widgets/Text/Text.hpp"
#include "../../GUI/Theme.hpp"


InitMenu::InitMenu(AppData& appData) : Menu{ appData } {
	// Construct title
	Text* title = new Text{ "PLATFORMS", _appData.assets.getFont("The Wireframe"), 165 };
	title->center(_appData.window);
	title->setFillColor(theme::Purple);
	addMenuItem(std::unique_ptr<Text>(title));
}

void InitMenu::update() {}
