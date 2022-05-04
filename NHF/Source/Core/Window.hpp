#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class App;


class Window {
private:
	static sf::RenderWindow _window;
	static std::function<sf::VideoMode()> _getVideoMode;

	sf::String _title = "Platforms";
	sf::ContextSettings _settings;
	sf::Uint32 _style = sf::Style::Fullscreen;
	static int _FPS;
	sf::Clock _clock;

	friend App;
	Window();

public:
	static const sf::RenderWindow& window() { return _window; }

	static sf::Vector2f getSize();
	static sf::FloatRect getLocalBounds();

	static void clear();
	static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
	static void display();

	void open() const;
	void close() const;
	bool isOpen() const;
	bool pollEvent(sf::Event& event) const;
	void lockFPS(int FPS = _FPS);
};
