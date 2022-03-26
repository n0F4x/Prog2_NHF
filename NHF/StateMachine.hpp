#pragma once

#include "State.hpp"


class StateMachine {
private:
	State* _currentState = nullptr;

protected:
	StateMachine(State* initialState);
	size_t getCurrentID() const;

public:
	void handleEvent(const sf::Event& event);
};
