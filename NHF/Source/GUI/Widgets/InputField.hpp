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

	void setActive(bool isActive);
	sf::Keyboard::Key _activeKey = sf::Keyboard::Unknown;
	std::string _activeString;
	bool _isActive = false;

	std::function<bool(const sf::Event::KeyEvent& keyEvent)> _contextSetter;
	std::function<std::string()> _contextGetter;

	// Override @MenuItem
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	InputField(
		const sf::Font& fontStyle,
		unsigned characterSize,
		const std::function<bool(const sf::Event::KeyEvent& event)>& contextSetter,
		const std::function<std::string()>& contextGetter
	);

	void setPosition(const sf::Vector2f& position) override;

	void center(const sf::Vector2f& window) override;
	void move(const sf::Vector2f& amount) override;

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
};