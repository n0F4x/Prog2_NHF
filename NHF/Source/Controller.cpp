#include "Controller.hpp"

#include "Controller/PreView.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/GameMenu.hpp"
#include "Menus/OptionsMenu.hpp"


Controller::Controller(Window& window) : _window{window} {}

void Controller::renderPreview() {
	_window.open();

	PreView::render();

	_preview = true;
}

void Controller::load() {
	sf::Clock clock;	// artificial delay

	_root = MenuNode{ std::make_unique<MainMenu>() };
	_current = &_root;
	_next = _current;

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
	}
	if (_current->get()->__isOpening__) {
		(_current->get()->__openLast__) ? openLast() : open(_current->get()->__next__);

		if (_next != nullptr) {
			_current->setLastVisitedChild(_next);
			_next->get()->init();
		}
	}

	if (_next == nullptr)
		return true;

	if (_current != _next) {
		_current->get()->pause();
		_current = _next;
		_current->get()->resume();
	}
	return true;
}

void Controller::open(const std::string& name) {
	_next = _current->findChild(name);
	_current->get()->__isOpening__ = false;
}
void Controller::openLast() {
	_next = _current->getLastVisitedChild();
	_current->get()->__openLast__ = false;
	_current->get()->__isOpening__ = false;
}
void Controller::close() {
	_next = _current->getParent();
	_current->get()->__isClosing__ = false;
}

MenuBase* Controller::operator->() const {
	return _current->get();
}
