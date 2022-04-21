#include "Menu.hpp"


void Menu::addMenuItem(std::unique_ptr<MenuItem> item) {
	_items.emplace_back(std::move(item));
}


void Menu::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left && event.key.alt) {
			Menu::close();
		}
		if (event.key.code == sf::Keyboard::Right && event.key.alt) {
			openLast();
		}
	}

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
	Window::clear();

	for (auto& item : _items) {
		Window::draw(*item);
	}

	Window::display();
}


void Menu::init() {
	__isClosing__ = false;
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
