#include "MainMenu.hpp"

#include "../GUI/Widgets/Button.hpp"


MainMenu::MainMenu() {
	// Construct "Exit" button
	auto exitButton = std::make_unique<Button>("Exit", AppData::assets.getFont("Dameron"), 76u, [this]() {Menu::close(true); });
	exitButton->setPosition({ Window::getSize().x - Window::getSize().x / 40.f - exitButton->getSize().x, Window::getSize().x / 40.f });

	// Construct "Play" button
	auto playButton = std::make_unique<Button>("Play", AppData::assets.getFont("Dameron"), 76u, [this]() { Menu::open("Game"); });
	playButton->center(Window::getLocalBounds());
	playButton->move(-1.f * sf::Vector2f{ 0,  playButton->getSize().y });

	// Construct "Options" button
	auto optionsButton = std::make_unique<Button>("Options", AppData::assets.getFont("Dameron"), 76u, [this]() { Menu::open("Options"); });
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
			Menu::open("Game");
		}
		if (event.key.code == sf::Keyboard::Num2) {
			Menu::open("Options");
		}
	}
}
