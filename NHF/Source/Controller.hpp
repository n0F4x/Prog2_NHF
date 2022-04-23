#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Menus/MenuNode.hpp"
#include "Utilities/STL/string.hpp"


class Controller {
private:
	MenuNode _root;

	MenuNode* _current = nullptr;
	MenuNode* _next = nullptr;

	void open(const util::string& name);
	void openLast();
	void close();

public:
	void construct();
	void init();

	bool isActive();

	void handleEvent(const sf::Event& event) const;
	void update() const;
	void render() const;
};
