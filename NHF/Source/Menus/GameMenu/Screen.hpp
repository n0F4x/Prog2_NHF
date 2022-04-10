#pragma once

#include <SFML/Graphics.hpp>
#include "PreCalculator.hpp"
#include "PlatformContainer.hpp"


class Screen : public sf::Drawable {
private:
	const PreCalculator& _preCalc;

	sf::VertexArray _screen;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Screen(const PreCalculator& preCalc);

	void update(const PlatformContainer& platforms);
};

