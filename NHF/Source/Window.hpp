#pragma once

#include <SFML/Graphics.hpp>


class Window {
private:
	static sf::RenderWindow _window;

public:
	Window() = delete;

	static void init();
	static const sf::RenderWindow& window() { return _window; }

	static sf::Vector2f getSize();
	static void close();
	static bool isOpen();
	static bool pollEvent(sf::Event& event);
	static void display();
	static void clear();
	static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
};
