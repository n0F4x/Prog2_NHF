#pragma once

#include <deque>
#include <random>
#include "Platform.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


class PlatformContainer : public sf::Drawable, public Transitionable {
private:
	const PreCalculator& _preCalc;
	std::deque<Platform> _platforms;
	float _platformWidth = 360_deg / 8;

	unsigned _counter = 0;
	const unsigned _scaleSpeed = 20;	//the lower the faster

	float _rotation = 0_deg;

	// Random generation
	std::mt19937 _randomEngine{ std::random_device{}() };
	int generateRandom(int from, int to);
	bool _random = true;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	explicit PlatformContainer(const PreCalculator& preCalc);

	float getPlatformWidth() const { return _platformWidth; }

	bool isInside(const PolarVector& point) const;
	bool AI_help(PolarVector playerFeet, int& switchingState);

	void rotate(float angle);
	void transition(const sf::Vector2f& amount) override { rotate(amount.x); }

	void update();
	void init(unsigned laneCount);
};

