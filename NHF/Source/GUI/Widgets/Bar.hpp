#pragma once

#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Widget.hpp"
#include "Text.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "../../Utilities//Math/Transitionable.hpp"
#include "../../Core/AppData/ContextManager.hpp"


class Emphasis : public sf::RectangleShape, public Transitionable {
	void transition(const sf::Vector2f& amount) override { move(amount); }
};


template<typename T>
class Bar : public Widget {
private:
	Transitions::Bezier::Ease _transition{ &_emphasis };

	std::vector<T> _contents;
	std::vector<Text> _texts;
	std::vector<sf::RectangleShape> _cells;
	Emphasis _emphasis;

	size_t _selected = 0;
	Context::Accessor _context;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Bar(
		float width, 
		const std::vector<T>& contents, 
		const std::vector<std::string>& labels, 
		const sf::Font& font,
		unsigned chararcterSize, 
		Context::Accessor context
	);

	void setPosition(const sf::Vector2f& position) override;

	void handleEvent(const sf::Event& event) override;
	void init() override;
};