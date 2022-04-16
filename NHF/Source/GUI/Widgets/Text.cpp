#include "Text.hpp"


Text::Text(const sf::String& text, const sf::Font& fontStyle, unsigned characterSize) : _text{ text, fontStyle, characterSize } {
	setSize({ _text.getLocalBounds().width, _text.getLocalBounds().height });

	sf::FloatRect rect = _text.getLocalBounds();
	_text.setOrigin({ rect.left + rect.width / 2.f, rect.top + rect.height / 2.f });
}
