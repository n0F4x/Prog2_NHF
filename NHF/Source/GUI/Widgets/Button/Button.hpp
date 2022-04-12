#pragma once

#include "../Widget.hpp"
#include "ButtonSM_Builder.hpp"


class Button : public Widget {
private:
	sf::Text _text;

	std::function<void()> _callback;
	
	
	friend ButtonSM_Builder;
	StateMachine _stateMachine;

	// Helpers
	bool isInside(const sf::Vector2f& point) const;
	void triggerCallback();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Button(
		AssetManager& assets,
		const sf::String& text,
		const sf::Font& fontStyle,
		unsigned characterSize,
		std::function<void()> callback
	);
	Button(const Button&) = delete;

	virtual void setPosition(const sf::Vector2f& position) override { Widget::setPosition(position); _text.setPosition(position); }

	virtual void center(const Window& window) override;

	void handleEvent(const sf::Event& event) override { _stateMachine.handleEvent(event); }
	void update() override;
};
