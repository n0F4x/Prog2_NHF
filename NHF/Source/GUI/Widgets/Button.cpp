#include "Button.hpp"

#include "../Theme.hpp"


bool Button::isInside(const sf::Vector2f& point) const {
	return _text.getGlobalBounds().contains(sf::Vector2f{ point });
	return true;
}

void Button::triggerCallback() {
	if (_callback)
		_callback();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_text); }


Button::Button(
	const sf::String& text,
	const sf::Font& fontStyle,
	unsigned characterSize,
	std::function<void()> callback
) :
	_text{ text, fontStyle, characterSize },
	_callback{ callback }
{
	setSize({ _text.getLocalBounds().width, _text.getLocalBounds().height });

	sf::FloatRect rect = _text.getLocalBounds();
	_text.setOrigin({ rect.left + rect.width / 2.f, rect.top + rect.height / 2.f });

	_text.setFillColor(theme::Primary);
}


void Button::handleEvent(const sf::Event& event) {
	if (isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
		_text.setFillColor(theme::Secondary);
	}
	else {
		_text.setFillColor(theme::Primary);
	}

	if (event.type == sf::Event::MouseButtonPressed) {
		if (isInside(sf::Vector2f{ sf::Mouse::getPosition() })) {
			triggerCallback();
		}
	}
}
