#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Controller;


class MenuBase {
private:
	friend Controller;
	bool __isExiting__ = false;
	bool __isClosing__ = false;
	bool __openLast__ = false;
	std::string __next__;

	void __init__() {
		__isClosing__ = false;
		__openLast__ = false;
		__next__.clear();
	}

protected:
	void open(const std::string_view& next) { __next__ = next; }
	void openLast() { __openLast__ = true; }
	void close() { __isClosing__ = true; }
	void exit() { __isExiting__ = true; }

public:
	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void init() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual ~MenuBase() = default;
};
