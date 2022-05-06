#pragma once

#include <functional>
#include <string>
#include "../Widget.hpp"
#include "Text.hpp"


class InputField : public Widget {
private:
	ContextRepr<sf::Event::KeyEvent> _context;

	Text _text;
	std::string _string;
	sf::RectangleShape _frame;

	sf::Clock _clock;
	void setActive(bool isActive);
	std::string _activeString;
	bool _isActive = false;

	// Override @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	InputField(
		const sf::Font& fontStyle,
		unsigned characterSize,
		const std::string_view& contextName
	);

	void setPosition(const sf::Vector2f& position) override;

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
};