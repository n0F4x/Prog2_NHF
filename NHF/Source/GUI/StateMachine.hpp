#pragma once

#include <vector>
#include <memory>
#include "State.hpp"


class SM_Builder;


class StateMachine {
private:
	std::vector<std::unique_ptr<State>> _states;
	State* _currentState = nullptr;

	friend SM_Builder;
	State& getState(size_t id) { return *_states.at(id); }
	void addState(std::unique_ptr<State> state) { _states.emplace_back(std::move(state)); }

public:
	StateMachine(const SM_Builder& builder);
	
	const State& current() const { _currentState; };

	void handleEvent(const sf::Event& event);
};


class SM_Builder {
protected:
	void addState(StateMachine& SM, std::unique_ptr<State> state) const { return SM.addState(std::move(state)); }
	State& getState(StateMachine& SM, size_t id) const { return SM.getState(id); }

public:
	virtual void buildStates(StateMachine& stateMachine) const = 0;
	virtual void buildTransitions(StateMachine& stateMachine) const = 0;
};

class SM_Engineer {
private:
	const SM_Builder& _builder;
public:
	SM_Engineer(const SM_Builder& builder) : _builder{ builder } {}
	void construct(StateMachine& stateMachine) const;
};