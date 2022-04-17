#pragma once

#include <list>
#include "Platform.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


class PlatformContainer : public sf::Drawable, public Transitionable {
private:
	const PreCalculator _preCalc;
	std::list<Platform> _platforms;

	int _counter = 0;
	const int _scaleSpeed = 20;	//the lower the faster

	float _rotation = 0_deg;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	PlatformContainer(const sf::Window& window);

	const std::list<Platform>& getList() const;

	void rotate(float angle);
	void transition(float amount) { rotate(amount); }

	void update();
	void init();
};

