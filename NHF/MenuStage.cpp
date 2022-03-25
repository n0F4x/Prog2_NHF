#include "MenuStage.hpp"

#include "GameStage.hpp"


MenuStage::MenuStage(AppData& appData) :
	_appData{ appData },
	_PlayButton{
		"Play",
		94,
		_appData.assets.getFont("Air Millhouse"),
		[&]() {_appData.stages.addStage(std::make_unique<GameStage>(GameStage{ _appData }), false); }
}
{
	_PlayButton.setPosition({
		_appData.window.getSize().x / 2 - _PlayButton.getSize().x / 2,
		_appData.window.getSize().y / 2 - _PlayButton.getSize().y / 2
		});
}

void MenuStage::handleEvent(const sf::Event& event) {
	_PlayButton.handleEvent(event);
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			_appData.stages.removeStage();

		if (event.key.code == sf::Keyboard::Space)
			_appData.stages.addStage(std::make_unique<GameStage>( _appData ), false);
		if (event.key.code == sf::Keyboard::Enter)
			_appData.stages.addStage(std::make_unique<GameStage>( _appData ), false);
	}
}

void MenuStage::update() {
	_PlayButton.update();
}

void MenuStage::render() {
	_appData.window.clear();
	_appData.window.draw(_PlayButton);
	_appData.window.display();
}
