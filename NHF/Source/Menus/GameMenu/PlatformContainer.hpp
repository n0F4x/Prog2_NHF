#pragma once

#include <deque>
#include <random>
#include "Platform.hpp"
#include "../../Utilities/Math/Transitionable.hpp"


/**
 * @brief Class for managing platforms
*/
class PlatformContainer : public sf::Drawable, public Transitionable {
private:
	const PreCalculator& _preCalc;
	std::deque<Platform> _platforms;
	float _platformWidth = 360_deg / 8;

	unsigned _counter = 0;
	unsigned _scaleSpeed = 20;	//the lower the faster

	float _rotation = 0_deg;

	// Random generation
	std::mt19937 _randomEngine{ std::random_device{}() };
	/**
	 * @brief	Generates a random number from a range
	 * @param from	Starting element of the range
	 * @param to	Last element of the range (the generated numbers will be less than this)
	 * @return	The generated number
	*/
	int generateRandom(int from, int to);
	bool _random = true;

	/**
	 * @brief	Draws platforms to the render target
	 * @param target	The render target
	 * @param states	The render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	/**
	 * @brief	Constructs a new platform container
	 * @param preCalc	Reference to a PreCalculator
	*/
	explicit PlatformContainer(const PreCalculator& preCalc);

	/**
	 * @brief	Gets the width of the individual platforms
	 * @return	The platform's width
	*/
	float getPlatformWidth() const { return _platformWidth; }

	/**
	 * @brief	Checks whether a point is on the platforms
	 * @param point	The point in question
	 * @return	True if it is on the platforms
	*/
	bool isInside(const PolarVector& point) const;
	/**
	 * @brief	A helper function for the algorithm inside the main menu.
	 *		Checks when the algorithmic player needs to jump, and sets switchingState for the Track class
	 * @param playerFeet	The coordinates of the player
	 * @param switchingState	Reference to the Track's switching state
	 * @return	True if the algorithm has to jump
	*/
	bool AI_help(PolarVector playerFeet, int& switchingState);

	/**
	 * @brief	Rotates all platforms by a given angle
	 * @param angle	The given angle
	*/
	void rotate(float angle);
	/**
	 * @brief	Calls rotate with the X coordinate of the given vector
	 * @param amount	The given vector
	*/
	void transition(const sf::Vector2f& amount) override { rotate(amount.x); }

	/**
	 * @brief	Updates the state of the platforms
	*/
	void update();
	/**
	 * @brief	Initializes the platforms
	 * @param laneCount	The number of lanes for the platforms to form
	 * @param speed	The amount of times a platform needs to be updated to move by a range of 1 platform
	*/
	void init(unsigned laneCount, unsigned speed);
};

