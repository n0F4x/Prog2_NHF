#pragma once

#include <SFML/Graphics.hpp>
#include "MenuNode.hpp"

struct AppData;


class MenuManager {
private:
	std::unique_ptr<MenuNode> _root;

	MenuNode* _current = nullptr;
	MenuNode* _next = nullptr;

public:
	void init(AppData& appData);

	bool isEmpty();

	void open(std::string name);
	void close();

	void handleEvent(const sf::Event& event);
	void update();
	void render();
};
