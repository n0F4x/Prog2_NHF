#include "InitMenu.hpp"

#include "Text.hpp"


InitMenu::InitMenu(AppData& appData) : Menu{ appData } {
	// Construct title
	Text title{ "Loading", _appData.assets.getFont("Game of Squids"), 84 };
	title.setPosition({
			_appData.window.getSize().x / 2 - title.getSize().x / 2,
			_appData.window.getSize().y / 2 - title.getSize().y / 2
		}
	);
	addMenuItem(std::make_unique<Text>(title));
}
