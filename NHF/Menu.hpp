#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "MenuItem.hpp"

struct AppData;


class Menu {
protected:
	AppData& _appData;
	std::vector<std::unique_ptr<MenuItem>> _items;
	void addMenuItem(std::unique_ptr<MenuItem> item);
	bool _isPaused = false;

public:
	Menu(AppData& appData);

	virtual void handleEvent(const sf::Event& event);
	virtual void update();
	virtual void render();
	virtual void init();
	virtual void pause();
	virtual void resume();

	virtual ~Menu() {}
};
