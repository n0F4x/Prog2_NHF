#include "MenuManager.hpp"

#include "InitMenu.hpp"
#include "MainMenu.hpp"
#include "GameMenu.hpp"


void MenuManager::init(AppData& appData) {
	_root = std::make_unique<MenuNode>(/*"Init", */std::make_unique<InitMenu>(appData));
	_current = _root.get();
	render();

	_root.reset();
	_root = std::make_unique<MenuNode>(/*"Main", */std::make_unique<MainMenu>(appData));
	_current = _root.get();
	_next = _current;

	_root->addChild("Game", std::make_unique<GameMenu>(appData));
}

bool MenuManager::isEmpty() {
	if (_next == nullptr)
		return true;

	if (_current != _next) {
		_current->get()->pause();
		_current = _next;
		_current->get()->resume();
	}
	return false;
}

void MenuManager::open(std::string name) {
	if (_current->getChildren().find(name) != _current->getChildren().end()) {
		_next = _current->getChildren().at(name).get();
		_next->get()->init();
	}
}
void MenuManager::close() {
	_next = _current->getParent();
}

void MenuManager::handleEvent(const sf::Event& event) { _current->get()->handleEvent(event); }
void MenuManager::update() { _current->get()->update(); }
void MenuManager::render() { _current->get()->render(); }
