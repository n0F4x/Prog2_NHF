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

	int _counter = 0;
	const int _scaleSpeed = 5;	//the lower the faster

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float _rotation = 0_deg;
	void rotate(float angle);

	bool _isDragged = false;
	sf::Vector2f _mouse;
	
	//int _switchDirection = 0;
	//float _rotationSpeed = 0_deg;
	//float _maxRotationSpeed = 5_deg;
	//float _rotationAcc = 0.5_deg;
	//void switchLane();


	void updatePlatforms();

public:
	Track(sf::Window& window, Engine& engine, const sf::Vector2f& mouse);

	void setMouse(const sf::Vector2f& mouse);

	void handleEvent(const sf::Event& event);
	void update();
};
