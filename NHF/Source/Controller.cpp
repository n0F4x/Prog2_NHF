#include "Controller.hpp"

#include "Menus/MenuNode.hpp"
#include "Menus/InitMenu.hpp"
#include "Menus/MainMenu.hpp"
#include "Menus/GameMenu.hpp"
#include "Menus/OptionsMenu.hpp"


Controller::Controller() : _root{ nullptr } {}

void Controller::init() {
	_root.reset();
	_root = std::make_unique<MenuNode>(std::make_unique<InitMenu>());
	_current = _root.get();
	render();

	sf::Clock clock;
	_root.reset();
	_root = std::make_unique<MenuNode>(std::make_unique<MainMenu>());
	_current = _root.get();
	_next = _current;

	// Build tree
	_root->addChild("Game", std::make_unique<GameMenu>());
	_root->addChild("Options", std::make_unique<OptionsMenu>());

	while (clock.getElapsedTime().asMilliseconds() < 2000);
}

bool Controller::isEmpty() {
	if (_current->get()->__isExiting__) {
		return true;
	}
	if (_current->get()->__isClosing__) {
		close();
	}
	if (_current->get()->__isOpening__) {
		if (_current->get()->__openLast__) {
			openLast();
			_current->get()->__openLast__ = false;
		}
		else {
			open(_current->get()->__next__);
		}
		_current->get()->__isOpening__ = false;
	}

	if (_next == nullptr)
		return false;

	if (_current != _next) {
		_current->get()->pause();
		_current = _next;
		_current->get()->resume();
	}
	return false;
}

void Controller::open(util::string name) {
	if (_current->getChildren().find(name) != _current->getChildren().end()) {
		_next = _current->getChildren().at(name).get();
		_next->get()->init();
		_current->_lastVisitedChild = _next;
	}
}
void Controller::openLast() {
	_next = _current->_lastVisitedChild;
	if (_next != nullptr) {
		_next->get()->init();
	}
}
void Controller::close() {
	_next = _current->getParent();
}

void Controller::handleEvent(const sf::Event& event) { _current->get()->handleEvent(event); }
void Controller::update() { _current->get()->update(); }
void Controller::render() { _current->get()->render(); }

Controller::~Controller() {}
