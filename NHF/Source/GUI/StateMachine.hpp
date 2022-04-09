#pragma once

#include "State.hpp"


class StateMachine {
private:
	State* _currentState = nullptr;

protected:
	StateMachine();
	void init(State* initState);
	size_t getCurrentID() const;

public:
	void handleEvent(const sf::Event& event);
};
