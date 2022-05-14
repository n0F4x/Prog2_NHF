#include "Menu.hpp"


void Menu::addMenuItem(std::unique_ptr<MenuItem> item) {
	_items.emplace_back(std::move(item));
}


void Menu::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left && event.key.alt) {
			close();
		}
		else if (event.key.code == sf::Keyboard::Right && event.key.alt) {
			openLast();
		}
	}

	for (const auto& item : _items) {
		item->handleEvent(event);
	}
}

void Menu::update() {
	for (const auto& item : _items) {
		item->update();
	}
}

void Menu::render() {
	Window::clear();

	for (const auto& item : _items) {
		Window::draw(*item);
	}

	Window::display();
}


void Menu::init() {
	for (const auto& item : _items) {
		item->init();
	}
	_isPaused = false;
}

void Menu::pause() {
	for (const auto& item : _items) {
		item->pause();
	}
	_isPaused = true;
}

void Menu::resume() {
	for (const auto& item : _items) {
		item->resume();
	}
	_isPaused = false;
}
