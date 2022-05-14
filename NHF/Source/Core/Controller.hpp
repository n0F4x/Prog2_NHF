#pragma once

#include "Controller/MenuNode.hpp"
#include "Window.hpp"


class App;


class Controller {
private:
	MenuNode _root;

	MenuNode* _current = nullptr;

	void open();
	void openLast();
	void close();

	Window& _window;
	bool _preview = false;

public:
	explicit Controller(Window& window);

	void renderPreview();
	void load();

	bool isActive();

	MenuBase* operator->() const;
};
