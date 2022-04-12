#include "StateMachine.hpp"


StateMachine::StateMachine(const SM_Builder& builder) {
	SM_Engineer engineer{ builder };
	engineer.construct(*this);
	_currentState = _states[0].get();
}

void StateMachine::handleEvent(const sf::Event& event) {
	_currentState = _states.at(_currentState->getNext(event)).get();
}


void SM_Engineer::construct(StateMachine& stateMachine) const {
	_builder.buildStates(stateMachine);
	_builder.buildTransitions(stateMachine);
}
