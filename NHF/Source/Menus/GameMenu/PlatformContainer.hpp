#pragma once

#include <list>
#include "Platform.hpp"


class PlatformContainer : public sf::Drawable{
private:
	std::list<Platform> _platforms;

	int _counter = 0;
	const int _scaleSpeed = 20;	//the lower the faster

	float _rotation = 0_deg;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	PlatformContainer(const sf::Window& window);

	const std::list<Platform>& getList() const;

	void rotate(float angle);

	void update();
	void init();
};

