#include "StateMachine.hpp"


StateMachine::StateMachine(State& initialState):
	_currentState{ initialState }
{}

void StateMachine::handleEvent(const sf::Event& event) {
	_currentState = _currentState.getNext(event);
}

size_t StateMachine::getCurrentID() const {
	return _currentState.getID();
}
