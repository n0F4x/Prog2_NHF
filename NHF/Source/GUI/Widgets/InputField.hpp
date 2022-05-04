#pragma once

#include <functional>
#include <string>
#include "../Widget.hpp"
#include "Text.hpp"


class InputField : public Widget {
private:
	sf::Clock _clock;

	Text _text;
	std::string _string;
	sf::RectangleShape _frame;

	void setActive(bool isActive);
	sf::Keyboard::Key _activeKey = sf::Keyboard::Unknown;
	std::string _activeString;
	bool _isActive = false;

	Context::Accessor _context;

	// Override @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	InputField(
		const sf::Font& fontStyle,
		unsigned characterSize,
		Context::Accessor context
	);

	void setPosition(const sf::Vector2f& position) override;

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
};