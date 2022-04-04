#pragma once

#include <memory>
#include <stack>

#include "Menu.hpp"


class MenuManager {
private:
	std::stack<std::unique_ptr<Menu>> _Menus;
	std::unique_ptr<Menu> _newMenu;

	bool _isRemoving = false;
	bool _isAdding = false;
	bool _isReplacing = false;

public:
	MenuManager() = default;
	MenuManager(std::unique_ptr<Menu> initialMenu);

	bool isEmpty();
	void processChanges();

	Menu& current();
	void addMenu(std::unique_ptr<Menu> newMenu, bool isReplacing = true);
	void removeMenu();
};
