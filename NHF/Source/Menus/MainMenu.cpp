#include "MainMenu.hpp"

#include "../GUI/Widgets/Button.hpp"


MainMenu::MainMenu() {
	// Construct "Exit" button
	Button* exitButton = new Button{ "Exit", AppData::assets.getFont("Dameron"), 76u, [this]() {Menu::close(true); } };
	exitButton->setPosition({ Window::getSize().x / 40.f, Window::getSize().x / 40.f });
	addMenuItem(std::unique_ptr<Button>{exitButton});

	// Construct "Play" button
	Button* playButton = new Button{ "Play", AppData::assets.getFont("Dameron"), 76u, [&]() { Menu::open("Game"); } };
	playButton->center(Window::getLocalBounds());
	playButton->move(-1.f * sf::Vector2f{ 0,  playButton->getSize().y });
	addMenuItem(std::unique_ptr<Button>{playButton});

	// Construct "Options" button
	Button* optionsButton = new Button{ "Options", AppData::assets.getFont("Dameron"), 76u, [&]() { Menu::open("Options"); } };
	optionsButton->center(Window::getLocalBounds());
	optionsButton->move(+1.f * sf::Vector2f{ 0, playButton->getSize().y });
	addMenuItem(std::unique_ptr<Button>{optionsButton});
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
