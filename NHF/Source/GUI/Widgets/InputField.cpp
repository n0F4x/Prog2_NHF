#include "InputField.hpp"

#include <cmath>
#include <algorithm>
#include "../../Window.hpp"
#include "../Theme.hpp"


void InputField::setActive(bool isActive) {
	if (isActive) {
		_text.setFillColor(theme::Secondary);
		_activeString.clear();
		_isActive = true;
		_clock.restart();
	}
	else {
		if (_activeString != "") {
			_string = _activeString;
		}
		_text.setString(_string);
		_text.setFillColor(theme::Primary);
		_text.center(_frame.getLocalBounds());
		_text.move(_frame.getPosition());
		_isActive = false;
	}
}


void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_text);
	target.draw(_frame);
}


InputField::InputField(
	const sf::Font& fontStyle,
	unsigned characterSize,
	Context::Accessor context
) :
	_text{ context.getContextString(), fontStyle, characterSize },
	_string{ context.getContextString() },
	_frame{ { Text{ "Ctrl+Alt+Shift+Space", fontStyle, characterSize }.getSize().x * 1.2f, _text.getSize().y * 2.f } },
	_context{ context }
{
	setSize(_frame.getSize());
	_text.center(_frame.getLocalBounds());
	_text.setFillColor(theme::Primary);
	_frame.setFillColor(sf::Color::Transparent);
	_frame.setOutlineThickness(2.f);
	_frame.setOutlineColor(theme::IndigoPurple);
}


void InputField::setPosition(const sf::Vector2f& position) {
	_text.setPosition(position + (_text.getPosition() - _position));
	_frame.setPosition(position);
	Widget::setPosition(position);
}


void InputField::handleEvent(const sf::Event& event) {
	if (!_isActive) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
			&& _frame.getGlobalBounds().contains(sf::Vector2f { sf::Mouse::getPosition(Window::window()) })
			) {
			setActive(true);
		}
	}
	else {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			setActive(false);
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Enter) {
				setActive(false);
			}
			else if (_context.setContext(event.key)) {
				_activeKey = event.key.code;
				_activeString = _context.getContextString();
			}
		}
		if (event.type == sf::Event::KeyReleased && event.key.code == _activeKey) {
			setActive(false);
		}
	}
}

void InputField::update() {
	if (_isActive) {
		if (_activeString == "") {
			if (static_cast<int>(floor(_clock.getElapsedTime().asSeconds() * 2.f)) % 2 == 0) {
				_text.setString("|");
			}
			else {
				_text.setString("");
			}
		}
		else {
			_text.setString(_activeString);
		}
		_text.center(_frame.getLocalBounds());
		_text.move(_frame.getPosition());
	}
}

void InputField::init() {
	setActive(false);
}
