#pragma once

#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Widget.hpp"
#include "Text.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "../../Utilities//Math/Transitionable.hpp"


class Emphasis : public sf::RectangleShape, public Transitionable {
	void transition(const sf::Vector2f amount) override { move(amount); }
};


class Bar : public Widget {
private:
	Transitions::Ease _transition{ &_emphasis };

	std::vector<Text> _contents;
	std::vector<sf::RectangleShape> _cells;
	Emphasis _emphasis;

	size_t _selected = 0;
	std::function<void(const std::string&)> _setContext;
	std::function<std::string ()> _getContext;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Bar(
		float width, const std::vector<std::string>& contents, const sf::Font& font, unsigned chararcterSize,
		const std::function<void(const std::string&)>& setContext, const std::function<std::string ()>& getContext
	);

	void setPosition(const sf::Vector2f& position) override;

	void center(const sf::Vector2f& window) override;
	void move(const sf::Vector2f& amount) override;

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void init() override;
};