#include "WindowManager.hpp"


WindowManager::WindowManager() : RenderWindow{} {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.sRgbCapable = true;

	create(sf::VideoMode::getDesktopMode(), "My Game", sf::Style::None, settings);

	setVerticalSyncEnabled(true);
	setKeyRepeatEnabled(false);
}
