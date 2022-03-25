#include "State.hpp"


State::State(size_t id) : _id{ id } {}

void State::setEventListener(std::function<State& (const sf::Event& event)> eventListener) {
	_eventListener = eventListener;
}

State& State::getNext(const sf::Event& event) {
	if (_eventListener) {
		return _eventListener(event);
	}
	return *this;
}

size_t State::getID() const {
	return _id;
}
