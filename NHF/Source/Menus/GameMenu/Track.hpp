#pragma once

#include "../../Menus/MenuItem.hpp"
#include "PreCalculator.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "PlatformContainer.hpp"


class Track : public MenuItem {
private:
	// Managed items
	PlatformContainer _platforms;

	// "Observables"
	sf::Window& _window;
	PreCalculator _preCalc;
	Transitions::EaseInOut _transition{ &_platforms, 100, Platform::width };


	// Variables
	bool _isPaused = false;
	sf::Vector2f _mouse;
	bool _isDragged = false;
	bool _switchingLeft = false;
	bool _switchingRight= false;


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
