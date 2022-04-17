#include "Bar.hpp"

#include "../Theme.hpp"


void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& text : _contents)
		target.draw(text);

	target.draw(_emphasis);

	for (const auto& cell : _cells)
		target.draw(cell);
}


Bar::Bar(float width, const std::vector<std::string>& contents, const sf::Font& font, unsigned chararcterSize) {
	sf::Vector2f cellSize = { width / static_cast<float>(contents.size()), Text{ "0", font, chararcterSize }.getSize().y * 2.f };

	_cells.resize(contents.size());
	for (size_t i = 0; i < _cells.size(); i++) {
		_cells[i].setSize(cellSize);
		_cells[i].move({ cellSize.x * static_cast<float>(i), 0.f });
		_cells[i].setFillColor(sf::Color::Transparent);
		_cells[i].setOutlineColor(theme::Primary);
		_cells[i].setOutlineThickness(2.f);
	}

	_contents.resize(contents.size());
	for (size_t i = 0; i < _contents.size(); i++) {
		_contents[i] = Text{ contents[i].c_str(), font, chararcterSize };
		_contents[i].center(_cells[i].getSize());
		_contents[i].move(_cells[i].getPosition());
	}

	_emphasis.setSize(cellSize);
	_emphasis.setPosition(_cells[_selected].getPosition());
	_emphasis.setFillColor(theme::Tertiary);

	setSize({ cellSize.x * static_cast<float>(contents.size()), cellSize.y });
}


void Bar::setPosition(const sf::Vector2f& position) {
	for (sf::RectangleShape& cell : _cells) {
		cell.setPosition(position + (cell.getPosition() - _position));
	}
	for (Text& content : _contents) {
		content.setPosition(position + (content.getPosition() - _position));
	}

	_emphasis.setPosition(position + (_emphasis.getPosition() - _position));

	Widget::setPosition(position);
}

void Bar::setFillcolor(const sf::Color& color) {
	for (auto& content : _contents) {
		content.setFillColor(color);
	}
}


void Bar::center(const sf::Vector2f& window) {
	setPosition({ window.x / 2.f - getSize().x / 2.f, window.y / 2.f - getSize().y / 2.f });
}

void Bar::move(const sf::Vector2f& amount) {
	setPosition(_position + amount);
}


void Bar::handleEvent(const sf::Event& event) {}

void Bar::update() {}
