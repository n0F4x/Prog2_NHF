#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>


/**
 * @brief	Class for displaying the view. Adapter for sf::RenderWindow
*/
class Window {
private:
	static std::unique_ptr<sf::RenderWindow> _window;
	static std::function<sf::VideoMode()> _getVideoMode;

	sf::String _title = "Platforms";
	sf::ContextSettings _settings;
	sf::Uint32 _style = sf::Style::Fullscreen;
	sf::Clock _clock;

public:
	/**
	 * @brief	Getter for inner window
	 * @return	Inner window
	*/
	static const sf::RenderWindow& window() { return *_window; }

	/**
	 * @brief	Getter for the size of the window
	 * @return	The size of the window
	*/
	static sf::Vector2f getSize();
	/**
	 * @brief	Getter for the bounds of the window
	 * @return	The bounds of the window
	*/
	static sf::FloatRect getLocalBounds();

	/**
	 * @brief	Clears the window
	*/
	static void clear();
	/**
	 * @brief	Draws object to window
	 * @param drawable	Object to be drawn
	 * @param states	Render states
	*/
	static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
	/**
	 * @brief	Displays the contents of the window
	*/
	static void display();

	/**
	 * @brief	Constructs a new Window
	*/
	Window();
	/**
	 * @brief	Opens the window
	*/
	void open() const;
	/**
	 * @brief	Closes the window
	*/
	void close() const;
	/**
	 * @brief	Checks whether the window is open
	 * @return	True if the window is open
	*/
	bool isOpen() const;
	/**
	 * @brief	Calls pollEvent on the inner sf::RenderWindow
	 * @param event	Reference to event where information will be distributed
	 * @return	True in case a new event was polled
	*/
	bool pollEvent(sf::Event& event) const;
	/**
	 * @brief	Locks the number of frames per second.
			Makes sure by causing potential delay that the right amount of time has passed since the last call of the function
	 * @param FPS	Frames per second. Default is 60
	*/
	void lockFPS(int FPS = 60);
};
