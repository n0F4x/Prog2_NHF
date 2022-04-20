#include "InputField.hpp"

#include <cmath>
#include "../../Window.hpp"
#include "../Theme.hpp"


void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_text);
	target.draw(_frame);
}


InputField::InputField(
	const sf::String& text,
	const sf::Font& fontStyle,
	unsigned characterSize,
	std::function<bool(const sf::Event::KeyEvent& event, std::string& text)> eventHandler
) :
	_text{ text, fontStyle, characterSize },
	_string{ text },
	_frame{ {Text{"Ctrl+Alt+Shift+Space", fontStyle, characterSize}.getSize().x * 1.2f, _text.getSize().y * 2.f} },
	_eventHandler{ eventHandler }
{
	setSize(_frame.getSize());
	_text.center(_frame.getSize());
	_text.setFillColor(theme::IndigoPurple);
	_frame.setFillColor(theme::Tertiary);
	_frame.setOutlineThickness(2.f);
	_frame.setOutlineColor(theme::Primary);
}


void InputField::setPosition(const sf::Vector2f& position) {
	_text.setPosition(position + (_text.getPosition() - _position));
	_frame.setPosition(position);
	Widget::setPosition(position);
}

void InputField::center(const sf::Vector2f& window) {
	setPosition({ window.x / 2.f - getSize().x / 2.f, window.y / 2.f - getSize().y / 2.f });
}

void InputField::move(const sf::Vector2f& amount) {
	setPosition(_position + amount);
}


void InputField::handleEvent(const sf::Event& event) {
	if (!_isActive) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (_frame.getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition(Window::window()) })) {
					_isActive = true;
					_clock.restart();
				}
			}
		}
	}
	else {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				_isActive = false;
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
			case sf::Keyboard::Enter:
				_isActive = false;
				break;
			default:
				_isActive = _eventHandler(event.key, _string);
				break;
			}
		}
	}
}

void InputField::update() {
	if (_isActive) {
		if (static_cast<int>(floor(_clock.getElapsedTime().asSeconds() * 2.f)) % 2 == 0) {
			_text.setString("|");
			_text.center(_frame.getSize());
			_text.move(_frame.getPosition());
		}
		else {
			_text.setString("");
		}
	}
	else {
		_text.setString(_string);
		_text.center(_frame.getSize());
		_text.move(_frame.getPosition());
	}
}

void InputField::init() {
	_isActive = false;
}
