#include "InitMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI/Theme.hpp"


InitMenu::InitMenu() {
	// Construct title
	auto* title = new Text{ "PLATFORMS", AppData::assets.getFont("The Wireframe"), 186u };
	title->center(Window::getLocalBounds());
	title->setFillColor(theme::Secondary);
	addMenuItem(std::unique_ptr<Text>(title));
}
