#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Menus/MenuNode.hpp"
#include "Utilities/STL/string.hpp"

class App;


class Controller {
private:
	MenuNode _root;

	MenuNode* _current = nullptr;
	MenuNode* _next = nullptr;

	void open(const util::string& name);
	void openLast();
	void close();

	friend App;
	Controller();

public:
	void init();

	bool isActive();

	void handleEvent(const sf::Event& event) const;
	void update() const;
	void render() const;
};
