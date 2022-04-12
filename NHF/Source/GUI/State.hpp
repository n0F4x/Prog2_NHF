#pragma once

#include <functional>
#include <SFML/Graphics.hpp>


struct StateData {};


class State {
private:
	size_t _id;
	std::function<size_t (const sf::Event& event)> _eventListener = nullptr;
	StateData _data;

public:
	State(size_t id, StateData data) : _id{id}, _data{data} {}
	void setEventListener(std::function<size_t (const sf::Event& event)> eventListener) { _eventListener = eventListener; }
	size_t getNext(const sf::Event& event) { return (_eventListener != nullptr) ? _eventListener(event) : _id; }
	size_t getID() const { return _id; }
	const StateData& getData() const { return _data; }
};