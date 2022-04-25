#include "Controller.hpp"

#include "Menus/MainMenu.hpp"
#include "Menus/GameMenu.hpp"
#include "Menus/OptionsMenu.hpp"


void Controller::init() {
	// Reset root (optional)
	_root = MenuNode{ std::make_unique<MainMenu>() };
	_current = &_root;
	_next = _current;

	// Build tree
	_root.addChild("Game", std::make_unique<GameMenu>());
	_root.addChild("Options", std::make_unique<OptionsMenu>());
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

void Controller::open(const util::string& name) {
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

void Controller::handleEvent(const sf::Event& event) const { _current->get()->handleEvent(event); }
void Controller::update() const { _current->get()->update(); }
void Controller::render() const { _current->get()->render(); }
