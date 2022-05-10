#include "PauseScreen.hpp"

#include "../../GUI/Theme.hpp"


void PauseScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (isPaused()) {
		target.draw(_bg);
		target.draw(_text);
		target.draw(_backButton);
	}
}


PauseScreen::PauseScreen(const std::function<void()>& resumeMenu, const std::function<void()>& closeMenu) :
	_backButton{ "Back to\nMenu", AppData::getFont("Dameron"), 56u, [this, closeMenu]() {closeMenu(); pause();} },
	_resumeMenu{resumeMenu}
{
	sf::Color bgColor = { 0, 0, 0, 220 };
	_bg.setFillColor(bgColor);

	_text.center(Window::getLocalBounds());
	_text.setFillColor(theme::IndigoPurple);

	_backButton.setPosition({ Window::getSize().x / 40.f, Window::getSize().x / 40.f });
}

void PauseScreen::setText(const sf::String& text) {
	_text.setString(text);
}


void PauseScreen::handleEvent(const sf::Event& event) {
	if (isPaused()) {
		if (
			event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ||
			event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
			) {
			resume();
			_resumeMenu();
		}
		_backButton.handleEvent(event);
	}
}
