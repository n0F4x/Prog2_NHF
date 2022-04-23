#pragma once

#include "Bar.hpp"

#include "../Theme.hpp"
#include "../../Window.hpp"
#include "../../AppData.hpp"


template<typename T>
void Bar<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& text : _contents)
		target.draw(text);

	target.draw(_emphasis);

	for (const auto& cell : _cells)
		target.draw(cell);
}


template<typename T>
Bar<T>::Bar(
	float width, const std::vector<std::string>& contents, const sf::Font& font, unsigned chararcterSize,
	const std::function<void(const T&)>& setContext, const std::function<std::string ()>& getContext
) :
	_setContext{ setContext },
	_getContext{ getContext }
{
	sf::Vector2f cellSize = { width / static_cast<float>(contents.size()), Text{ "0", font, chararcterSize }.getSize().y * 2.f };

	_cells.resize(contents.size());
	for (size_t i = 0; i < _cells.size(); i++) {
		_cells[i].setSize(cellSize);
		_cells[i].move({ cellSize.x * static_cast<float>(i), 0.f });
		_cells[i].setFillColor(sf::Color::Transparent);
		_cells[i].setOutlineColor(theme::IndigoPurple);
		_cells[i].setOutlineThickness(2.f);
	}

	_contents.resize(contents.size());
	for (size_t i = 0; i < _contents.size(); i++) {
		_contents[i] = Text{ contents[i].c_str(), font, chararcterSize };
		_contents[i].center(_cells[i].getLocalBounds());
		_contents[i].move(_cells[i].getPosition());
		_contents[i].setFillColor(theme::IndigoPurple);
	}

	_emphasis.setSize(cellSize);
	_emphasis.setPosition(_cells[_selected].getPosition());
	_emphasis.setFillColor(theme::Tertiary);

	setSize({ cellSize.x * static_cast<float>(contents.size()), cellSize.y });
}


template<typename T>
void Bar<T>::setPosition(const sf::Vector2f& position) {
	for (sf::RectangleShape& cell : _cells) {
		cell.setPosition(position + (cell.getPosition() - _position));
	}
	for (Text& content : _contents) {
		content.setPosition(position + (content.getPosition() - _position));
	}

	_emphasis.setPosition(position + (_emphasis.getPosition() - _position));

	Widget::setPosition(position);
}


template<typename T>
void Bar<T>::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		for (size_t i = 0; i < _cells.size(); i++) {
			if (_cells[i].getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition(Window::window()) })) {
				_setContext(_contents[i].getString());
				_transition.start(_cells[i].getPosition() - _emphasis.getPosition(), 200);
			}
		}
	}
}

template<typename T>
void Bar<T>::update() { _transition.update(); }

template<typename T>
void Bar<T>::init() {
	for (size_t i = 0; i < _contents.size(); i++) {
		if (_contents[i].getString() == _getContext()) {
			_emphasis.setPosition(_cells[i].getPosition());
		}
	}
	_transition.init();
}
