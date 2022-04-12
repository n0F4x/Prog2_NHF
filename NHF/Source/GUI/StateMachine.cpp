#include "StateMachine.hpp"


StateMachine::StateMachine(const SM_Builder& builder) {
	SM_Engineer engineer{ builder };
	engineer.construct(*this);
	_currentState = _states[0].get();
}

void StateMachine::handleEvent(const sf::Event& event) {
	_currentState = _currentState->getNext(event);
}


void SM_Engineer::construct(StateMachine& stateMachine) const {
	_builder.buildStates(stateMachine);
	_builder.buildTransitions(stateMachine);
}
