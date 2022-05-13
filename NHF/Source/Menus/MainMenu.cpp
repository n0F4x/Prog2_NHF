#include "MainMenu.hpp"

#include "../GUI/Widgets/Button.hpp"


MainMenu::MainMenu() {
	/**/ //////////////////////////
	/**/ //	Construct Background //
	/**/ //////////////////////////
	/**/ auto track = std::make_unique<TrackAI>();
	/**/ _track = track.get();
	/**/ addMenuItem(std::move(track));
	/**/
	/**/ auto player = std::make_unique<PlayerAI>();
	/**/ sf::Vector2f playerPos = Window::getSize() / 2.f + sf::Vector2f{ 0.f, Window::getSize().y / 2.5f };
	/**/ player->setPosition(playerPos);
	/**/ _player = player.get();
	/**/ addMenuItem(std::move(player));
	/**/
	/**/ addMenuItem(std::make_unique<Shader>());
	/**/ //////////////////////////

	// Construct "Exit" button
	auto exitButton = std::make_unique<Button>("Exit", AppData::getFont("Dameron"), 76u, [this]() { exit(); });
	exitButton->setPosition({ Window::getSize().x - Window::getSize().x / 40.f - exitButton->getSize().x, Window::getSize().x / 40.f });

	// Construct "Play" button
	auto playButton = std::make_unique<Button>("Play", AppData::getFont("Dameron"), 76u, [this]() { open("Game"); });
	playButton->center(Window::getLocalBounds());
	playButton->move(-1.f * sf::Vector2f{ 0,  playButton->getSize().y });

	// Construct "Options" button
	auto optionsButton = std::make_unique<Button>("Options", AppData::getFont("Dameron"), 76u, [this]() { open("Options"); });
	optionsButton->center(Window::getLocalBounds());
	optionsButton->move(+1.f * sf::Vector2f{ 0, playButton->getSize().y });

	// Add items to Menu
	addMenuItem(std::move(exitButton));
	addMenuItem(std::move(playButton));
	addMenuItem(std::move(optionsButton));
}

void MainMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Num1) {
			open("Game");
		}
		if (event.key.code == sf::Keyboard::Num2) {
			open("Options");
		}
	}
}

void MainMenu::update() {
	Menu::update();

	if (!_player->isJumping() && _track->AI_jump(_player->getFeet())) {
		_player->jump();
	}
}
