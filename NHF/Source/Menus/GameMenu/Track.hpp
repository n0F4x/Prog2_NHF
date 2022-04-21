#pragma once

#include "../../Menus/MenuItem.hpp"
#include "PreCalculator.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "PlatformContainer.hpp"


class Track : public MenuItem {
private:
	// "Observables"
	PreCalculator _preCalc;
	Transitions::EaseInOut _transition{ &_platforms };

	// Managed items
	PlatformContainer _platforms;
	sf::VertexArray _shader;

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
	Track();

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
	void pause() override;
	void resume() override;
};
