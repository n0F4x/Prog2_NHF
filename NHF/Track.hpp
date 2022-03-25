#pragma once

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Platform.hpp"


class Track : public sf::Drawable {
private:
	sf::Window& _window;
	Engine& _engine;

	sf::VertexArray _screen;
	std::list<Platform> _platforms;

	sf::Vector2f _origin;
	int _counter = 0;
	const int _scaleSpeed = 20;	//the lower the faster

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isInside(const sf::Vector2f& point) const;

	Angle _rotation = 0_deg;
	void rotate(Angle angle);

	bool _isDragged = false;
	sf::Vector2f _mouse;

	void updatePlatforms();

public:
	Track(sf::Window& window, Engine& engine, const sf::Vector2f& mouse);
	//~Track();

	void setMouse(const sf::Vector2f& mouse);

	void handleEvent(const sf::Event& event);
	void update();
};
