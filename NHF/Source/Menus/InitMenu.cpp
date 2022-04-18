#include "InitMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI/Theme.hpp"


InitMenu::InitMenu() {
	// Construct title
	Text* title = new Text{ "PLATFORMS", _appData.assets.getFont("The Wireframe"), 165u };
	title->center(_window.getSize());
	title->setFillColor(theme::Purple);
	addMenuItem(std::unique_ptr<Text>(title));
}
