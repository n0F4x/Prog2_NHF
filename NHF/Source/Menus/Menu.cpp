#include "Menu.hpp"

#include "../AppData/AppData.hpp"


void Menu::addMenuItem(std::unique_ptr<MenuItem> item) {
	_items.emplace_back(std::move(item));
}

Menu::Menu(AppData& appData) : _appData{ appData } {}

void Menu::handleEvent(const sf::Event& event) {
	for (auto& item : _items) {
		item->handleEvent(event);
	}
}

void Menu::update() {
	for (auto& item : _items) {
		item->update();
	}
}

void Menu::render() {
	_appData.window.clear();

	for (auto& item : _items) {
		_appData.window.draw(*item);
	}

	_appData.window.display();
}

void Menu::init() {
	for (auto& item : _items) {
		item->init();
	}
}

void Menu::pause() {
	for (auto& item : _items) {
		item->pause();
	}
	_isPaused = true;
}

void Menu::resume() {
	for (auto& item : _items) {
		item->resume();
	}
	_isPaused = false;
}
