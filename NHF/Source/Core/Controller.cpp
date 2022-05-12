#include "Controller.hpp"

#include "Controller/PreView.hpp"
#include "../Menus/MainMenu.hpp"
#include "../Menus/GameMenu.hpp"
#include "../Menus/OptionsMenu.hpp"


Controller::Controller(Window& window) : _window{ window } {}


void Controller::renderPreview() {
	_window.open();

	PreView::render();

	_preview = true;
}

void Controller::load() {
	sf::Clock clock;	// artificial delay for preview

	// Create root
	_root = MenuNode{ std::make_unique<MainMenu>() };
	_current = &_root;

	// Build tree
	_root.addChild("Game", std::make_unique<GameMenu>());
	_root.addChild("Options", std::make_unique<OptionsMenu>());

	if (_preview) {
		while (clock.getElapsedTime().asMilliseconds() < 2000);
	}
}


bool Controller::isActive() {
	if (_current->get()->__isExiting__) {
		return false;
	}
	if (_current->get()->__isClosing__) {
		close();
		return true;
	}
	if (_current->get()->__openLast__) {
		openLast();
		return true;
	}
	if (!_current->get()->__next__.empty()) {
		open();
		return true;
	}
	return true;
}

void Controller::open() {
	if (auto next = _current->findChild(_current->get()->__next__); next != nullptr) {
		_current->get()->pause();
		_current->setLastVisitedChild(next);
		_current = next;
		_current->get()->__init__();
		_current->get()->init();
	}
}
void Controller::openLast() {
	if (auto next = _current->getLastVisitedChild(); next != nullptr) {
		_current->get()->pause();
		_current = next;
		_current->get()->__init__();
		_current->get()->init();
	}
}
void Controller::close() {
	if (auto next = _current->getParent(); next != nullptr) {
		_current = next;
		_current->get()->__init__();
		_current->get()->resume();
	}
}

MenuBase* Controller::operator->() const {
	return _current->get();
}
