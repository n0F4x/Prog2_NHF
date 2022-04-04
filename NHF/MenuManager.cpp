#include "MenuManager.hpp"


void MenuManager::addMenu(std::unique_ptr<Menu> newMenu, bool isReplacing) {
	_isAdding = true;
	_isReplacing = isReplacing;

	_newMenu = std::move(newMenu);
}

void MenuManager::removeMenu() {
	_isRemoving = true;
}

MenuManager::MenuManager(std::unique_ptr<Menu> initialMenu) {
	_Menus.push(std::move(initialMenu));
}

bool MenuManager::isEmpty() {
	return _Menus.empty();
}

void MenuManager::processChanges() {
	if (_isRemoving) {
		if (!_Menus.empty()) {
			_Menus.pop();

			if (!_Menus.empty()) {
				_Menus.top()->resume();
			}
		}
		_isRemoving = false;
	}

	if (_isAdding) {
		if (!_Menus.empty()) {
			if (_isReplacing)
				_Menus.pop();
			else
				_Menus.top()->pause();
		}

		_Menus.push(std::move(_newMenu));
		_isAdding = false;
	}
}

Menu& MenuManager::current() {
	return *_Menus.top();
}
