#pragma once

#include <SFML/Graphics.hpp>


class Window {
private:
	static sf::RenderWindow _window;

public:
	void init();
	const sf::RenderWindow& operator()() const { return _window; }
	sf::RenderWindow& operator()() { return _window; }

	sf::Vector2f getSize() const;
	void close();
	bool isOpen() const;
	bool pollEvent(sf::Event& event);
	void display();
	void clear();
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
};
