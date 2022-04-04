#include "MainMenu.hpp"

#include "GameMenu.hpp"


MainMenu::MainMenu(AppData& appData) :
	_appData{ appData },
	_PlayButton{
		_appData.assets,
		"Play",
		56,
		_appData.assets.getFont("Dameron"),
		[&]() {_appData.menus.addMenu(std::make_unique<GameMenu>(GameMenu{ _appData }), false); }
}
{
	_PlayButton.setPosition({
		_appData.window.getSize().x / 2 - _PlayButton.getSize().x / 2,
		_appData.window.getSize().y / 2 - _PlayButton.getSize().y / 2
		});
}

void MainMenu::handleEvent(const sf::Event& event) {
	_PlayButton.handleEvent(event);
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.menus.removeMenu();
	}
}

void MainMenu::update() {
	_PlayButton.update();
}

void MainMenu::render() {
	_appData.window.clear();
	_appData.window.draw(_PlayButton);
	_appData.window.display();
}
