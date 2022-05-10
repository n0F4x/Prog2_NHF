#include "PauseScreen.hpp"

#include "../../GUI/Theme.hpp"


void PauseScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (isPaused()) {
		target.draw(_bg);
		target.draw(_text);
		target.draw(_backButton);
		target.draw(_playAgainButton);
	}
}


PauseScreen::PauseScreen(const std::function<void()>& resumeMenu, const std::function<void()>& closeMenu, const std::function<void()>& initMenu) :
	_backButton{ "Back to\nMenu", AppData::getFont("Dameron"), 56u, [this, closeMenu]() {closeMenu(); pause();} },
	_playAgainButton{ "Play\nAgain!", AppData::getFont("Dameron"), 56u, initMenu },
	_resumeMenu{resumeMenu}
{
	sf::Color bgColor = { 0, 0, 0, 220 };
	_bg.setFillColor(bgColor);

	_text.center(Window::getLocalBounds());
	_text.setFillColor(theme::IndigoPurple);

	_backButton.setPosition({ Window::getSize().x / 40.f, Window::getSize().x / 40.f });
	_playAgainButton.setPosition({ Window::getSize().x - Window::getSize().x / 40.f - _playAgainButton.getSize().x, Window::getSize().x / 40.f });
}

void PauseScreen::gameOver() {
	_text.setString("Game Over");
	_gameOver = true;
}


void PauseScreen::handleEvent(const sf::Event& event) {
	if (isPaused()) {
		if (
			event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ||
			event.type == sf::Event::KeyPressed && (
				event.key.code == sf::Keyboard::Space &&
				event.key.code != AppData::findContext("jumpKey")->get<sf::Event::KeyEvent>().code
				)
			) {
			_resumeMenu();
		}
		_playAgainButton.handleEvent(event);
		_backButton.handleEvent(event);
	}
}

void PauseScreen::init() {
	MenuItem::init();
	_text.setString("Resume");
	_backButton.init();
	_playAgainButton.init();
	_gameOver = false;
}
