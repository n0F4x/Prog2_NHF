#pragma once

#include "Controller/MenuNode.hpp"
#include "Window.hpp"


class App;


class Controller {
private:
	MenuNode _root;

	MenuNode* _current = nullptr;
	MenuNode* _next = nullptr;

	void open(const std::string& name);
	void openLast();
	void close();

	Window& _window;

	friend App;
	explicit Controller(Window& window);

	bool _preview = false;

public:
	void renderPreview();
	void load();

	bool isActive();

	MenuBase* operator->() const;
};
