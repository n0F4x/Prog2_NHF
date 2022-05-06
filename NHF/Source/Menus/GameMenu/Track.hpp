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
	PlatformContainer _platforms{ _preCalc };
	sf::VertexArray _shader{ sf::TriangleFan };

	// Variables
	sf::Vector2f _mouse{ sf::Vector2f{sf::Mouse::getPosition(Window::window())} };
	bool _isDragged = false;
	int _switchingState = 0;
	bool _switchingLeft = false;
	bool _switchingRight = false;

	void switchLanes();

	// Contexts
	ContextRepr<PlatformControl> _platformControl{ AppData::findContext("platformControl") };
	ContextRepr<sf::Event::KeyEvent> _switchKey1{ AppData::findContext("switchKey1") };
	ContextRepr<sf::Event::KeyEvent> _switchKey2{ AppData::findContext("switchKey2") };
	ContextRepr<bool> _holdSwitch{ AppData::findContext("holdSwitch") };


	// Overriding @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Track();

	bool isOnPlatform(const sf::Vector2f& point) const;

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
	void resume() override;
};
