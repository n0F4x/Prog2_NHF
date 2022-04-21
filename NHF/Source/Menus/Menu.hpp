#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Utilities/STL/vector.hpp"
#include "../Utilities/STL/string.hpp"
#include "MenuItem.hpp"
#include "../AppData.hpp"
#include "../Window.hpp"


class Menu {
private:
	util::vector<std::unique_ptr<MenuItem>> _items;

protected:
	bool _isPaused = false;

	void addMenuItem(std::unique_ptr<MenuItem> item);
	
	void open(const util::string& next) { __isOpening__ = true; __next__ = next; }
	void openLast() { __isOpening__ = true; __openLast__ = true; }
	void close(bool isExiting = false) { __isClosing__ = true; __isExiting__ = isExiting; }

public:
	bool __isClosing__ = false;
	bool __isExiting__ = false;
	bool __isOpening__ = false;
	bool __openLast__ = false;
	util::string __next__;

	virtual void handleEvent(const sf::Event& event);
	virtual void update();
	virtual void render();

	virtual void init();
	virtual void pause();
	virtual void resume();

	virtual ~Menu() {}
};
