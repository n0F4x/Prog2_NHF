#pragma once

#include <memory>
#include "../Utilities/STL/vector.hpp"
#include "../Core/Controller/MenuBase.hpp"
#include "../Core/AppData.hpp"
#include "../Core/Window.hpp"
#include "MenuItem.hpp"


class Menu : public MenuBase {
private:
	util::vector<std::unique_ptr<MenuItem>> _items;

	bool _isPaused = false;
	bool _renderDisplay = true;

protected:
	void addMenuItem(std::unique_ptr<MenuItem> item);

	bool isPaused() const { return _isPaused; }
	void setRenderDisplay(bool display) { _renderDisplay = display; }

public:
	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;

	void init() override;
	void pause() override;
	void resume() override;
};
