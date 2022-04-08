#include "StateMachine.hpp"


StateMachine::StateMachine() {}

void StateMachine::init(State* initState) {
	_currentState = initState;
}

void StateMachine::handleEvent(const sf::Event& event) {
	_currentState = _currentState->getNext(event);
}

size_t StateMachine::getCurrentID() const {
	return _currentState->getID();
}
