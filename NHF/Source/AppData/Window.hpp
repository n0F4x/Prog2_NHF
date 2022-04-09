#pragma once

#include <SFML/Graphics.hpp>
#include "MenuManager.hpp"


class Window: public sf::RenderWindow {
private:
	MenuManager& _controller;
	sf::Event _event;

public:
	Window(MenuManager& menus);
	void init();
	bool isRunning();

	void pollEvents();
};
