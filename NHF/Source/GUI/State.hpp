#pragma once

#include <functional>
#include <SFML/Graphics.hpp>


class State {
private:
	size_t _id;
	std::function<State* (const sf::Event& event)> _eventListener = nullptr;

public:
	State(size_t id);
	void setEventListener(std::function<State* (const sf::Event& event)> eventListener);
	State* getNext(const sf::Event& event);
	size_t getID() const;
};