#pragma once

#include "Controller/MenuNode.hpp"
#include "Utilities/STL/string.hpp"
#include "Menus/InitMenu.hpp"

class App;


class Controller {
private:
	MenuNode _root{ std::make_unique<InitMenu>() };

	MenuNode* _current = &_root;
	MenuNode* _next = _current;

	void open(const util::string& name);
	void openLast();
	void close();

	friend App;
	Controller() = default;

public:
	void init();

	bool isActive();

	void handleEvent(const sf::Event& event) const;
	void update() const;
	void render() const;
};
