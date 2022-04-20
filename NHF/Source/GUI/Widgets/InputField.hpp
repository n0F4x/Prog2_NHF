#pragma once

#include <functional>
#include <string>
#include "../Widget.hpp"
#include "Text.hpp"
#include "../../AppData.hpp"


class InputField : public Widget {
private:
	sf::Clock _clock;

	Text _text;
	std::string _string;
	sf::RectangleShape _frame;

	bool _isActive = false;
	std::function<bool(const sf::Event::KeyEvent& event, std::string& text)> _eventHandler;

	// Override @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	InputField(
		const sf::String& text,
		const sf::Font& fontStyle,
		unsigned characterSize,
		std::function<bool(const sf::Event::KeyEvent& event, std::string& text)> eventHandler
	);

	void setPosition(const sf::Vector2f& position) override;

	void center(const sf::Vector2f& window) override;
	void move(const sf::Vector2f& amount) override;

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
};