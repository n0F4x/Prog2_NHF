#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Utilities/STL/string.hpp"

class MenuNode;


class Controller {
private:
	std::unique_ptr<MenuNode> _root;

	MenuNode* _current = nullptr;
	MenuNode* _next = nullptr;

	void open(util::string name);
	void close();

public:
	Controller();
	Controller(const Controller&) = delete;

	void init();

	bool isEmpty();

	void handleEvent(const sf::Event& event);
	void update();
	void render();

	~Controller();
};
