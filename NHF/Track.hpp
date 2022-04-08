#pragma once

#include "MenuItem.hpp"
#include "PreCalculator.hpp"
#include "Screen.hpp"
#include "PlatformContainer.hpp"


class Track : public MenuItem {
private:
	// "Observables"
	sf::Window& _window;
	PreCalculator _preCalc;

	// Managed items
	Screen _screen;
	PlatformContainer _platforms;

	// Variables
	bool _isPaused = false;
	sf::Vector2f _mouse;
	bool _isDragged = false;


private:
	// Overriding @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Track(sf::Window& window);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
	void pause() override;
	void resume() override;
};
