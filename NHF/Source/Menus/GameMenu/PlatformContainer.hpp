#pragma once

#include <list>
#include <random>
#include "Platform.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


class PlatformContainer : public sf::Drawable, public Transitionable {
private:
	const PreCalculator& _preCalc;
	std::list<Platform> _platforms;

	int _counter = 0;
	const int _scaleSpeed = 20;	//the lower the faster

	float _rotation = 0_deg;

	// Random generation
	std::mt19937 _randomEngine{ std::random_device{}() };
	int generateRandom(int from, int to);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	explicit PlatformContainer(const PreCalculator& preCalc);

	bool isInside(const sf::Vector2f& point) const;

	void rotate(float angle);
	void transition(const sf::Vector2f& amount) override { rotate(amount.x); }

	void update();
	void init();
};

