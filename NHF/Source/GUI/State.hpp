#pragma once

#include <functional>
#include <SFML/Graphics.hpp>


struct StateData {};


class State {
private:
	size_t _id;
	std::function<State* (const sf::Event& event)> _eventListener = nullptr;
	StateData _data;

public:
	State(size_t id, StateData data) : _id{id}, _data{data} {}
	void setEventListener(std::function<State* (const sf::Event& event)> eventListener) { _eventListener = eventListener; }
	State* getNext(const sf::Event& event) { return (_eventListener != nullptr) ? _eventListener(event) : this; }
	size_t getID() const { return _id; }
	const StateData& getData() const { return _data; }
};