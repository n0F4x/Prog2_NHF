#pragma once

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Platform.hpp"


class Track : public sf::Drawable {
private:
	sf::Window& _window;
	Engine& _engine;

	const size_t _screenSize;
	sf::VertexArray _screen;
	std::list<Platform> _platforms;

	int _counter = 0;
	const int _scaleSpeed = 20;	//the lower the faster

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float _rotation = 0_deg;
	void rotate(float angle);

	bool _isDragged = false;
	sf::Vector2f _mouse;

	void updatePlatforms();

public:
	Track(sf::Window& window, Engine& engine, const sf::Vector2f& mouse);

	void setMouse(const sf::Vector2f& mouse);

	void handleEvent(const sf::Event& event);
	void update();
	void init();
};
