#pragma once

#include "MenuItem.hpp"
#include "PreCalculator.hpp"
#include "Transitions.hpp"
#include "PlatformContainer.hpp"
#include "AppData.hpp"
#include "Window.hpp"


class Track : public MenuItem {
private:
	// "Observables"
	PreCalculator _preCalc;
	Transitions::EaseInOut _transition{ &_platforms };

	// Managed items
	PlatformContainer _platforms{ _preCalc };

	// Variables
	sf::Vector2f _mouse{ sf::Vector2f{} };
	bool _isDragged = false;
	bool _switchingLeft = false;
	bool _switchingRight= false;


	// Overriding @MenuItem
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

public:
	Track();

	bool isOnPlatform(const sf::Vector2f& point) const;

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
	void resume() override;
};
