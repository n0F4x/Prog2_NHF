#include "WindowManager.hpp"

#include <iostream>


WindowManager::WindowManager() : RenderWindow{} {
	create(sf::VideoMode::getDesktopMode(), "My Game", sf::Style::None);

	setVerticalSyncEnabled(true);
	setKeyRepeatEnabled(false);
}
