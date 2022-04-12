#pragma once

#include "../../StateMachine.hpp"
#include "../../../AppData/AssetManager.hpp"


class Button;


struct ButtonStateData : public StateData {
	const sf::Color _color;

	ButtonStateData(const sf::Color& color) : _color{color} {}
};

class ButtonSM_Builder : public SM_Builder {
private:
	AssetManager& _assets;

	Button& _button;

public:
	ButtonSM_Builder(Button& button, AssetManager& assets) : _button{ button }, _assets{ assets } {}
	ButtonSM_Builder(const ButtonSM_Builder&) = default;

	void buildStates(StateMachine& stateMachine) const final;
	void buildTransitions(StateMachine& stateMachine) const final;
};
