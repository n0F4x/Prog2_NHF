#include "Button.hpp"


bool Button::isInside(const sf::Vector2f& point) const {
	return _text.getGlobalBounds().contains(sf::Vector2f{ point });
}

void Button::triggerCallback() {
	if (_callback)
		_callback();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(_text); }


Button::Button(
	AssetManager& assets,
	const sf::String& text,
	const sf::Font& fontStyle,
	unsigned characterSize,
	std::function<void()> callback
) :
	_text{ text, fontStyle, characterSize },
	_callback{ callback },
	_stateMachine{ ButtonSM_Builder{*this, assets} }
{
	setSize({ _text.getLocalBounds().width, _text.getLocalBounds().height });

	sf::FloatRect rect = _text.getLocalBounds();
	_text.setOrigin({ rect.left + rect.width / 2.f, rect.top + rect.height / 2.f });
}


void Button::center(const Window& window) { setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f }); }


void Button::update() {
	_text.setFillColor(sf::Color::Red);
}
