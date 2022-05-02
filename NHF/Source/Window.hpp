#pragma once

#include "SFMLRect.hpp"
#include "SFMLVector2.hpp"
#include "SFMLDrawable.hpp"
#include "SFMLEvent.hpp"
#include <functional>

class App;


class Window {
private:
	friend App;
	Window() = default;

	// NHF3:
	static bool _isOpen;

public:
	static sf::Vector2f getSize();
	static sf::FloatRect getLocalBounds();

	static void clear();
	static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = {});
	static void display();

	void open() const;
	void close() const;
	bool isOpen() const;
	bool pollEvent(const sf::Event& event) const;
};
