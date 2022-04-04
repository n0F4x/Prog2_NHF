#include "InitMenu.hpp"


InitMenu::InitMenu(AppData& appData) : 
	_appData{ appData },
	_text{"Loading", appData.assets.getFont("Game of Squids"), 84}
{
	_text.setPosition({
		_appData.window.getSize().x / 2 - _text.getGlobalBounds().width / 2,
		_appData.window.getSize().y / 2 - _text.getGlobalBounds().height / 2
		});
}


void InitMenu::handleEvent(const sf::Event&) {}

void InitMenu::update() {}

void InitMenu::render() {
	_appData.window.clear();

	_appData.window.draw(_text);

	_appData.window.display();
}
