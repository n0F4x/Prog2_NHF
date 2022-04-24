#pragma once

#include <memory>
#include "../Utilities/STL/vector.hpp"
#include "../Controller/MenuBase.hpp"
#include "../AppData.hpp"
#include "../Window.hpp"
#include "MenuItem.hpp"


class Menu : public MenuBase {
private:
	util::vector<std::unique_ptr<MenuItem>> _items;

	bool _isPaused = false;

protected:
	void addMenuItem(std::unique_ptr<MenuItem> item);

	bool isPaused() const { return _isPaused; }

public:
	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;

	void init() override;
	void pause() override;
	void resume() override;
};
