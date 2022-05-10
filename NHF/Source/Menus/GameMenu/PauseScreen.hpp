#include "../MenuItem.hpp"

#include "../../GUI/Widgets/Text.hpp"
#include "../../GUI/Widgets/Button.hpp"


class PauseScreen : public MenuItem {
private:
	sf::RectangleShape _bg{Window::getSize()};
	Text _text{ "Resume", AppData::getFont("Dameron"), 80u };
	Button _backButton{ "Back to Menu", AppData::getFont("Dameron"), 56u};

	const std::function<void()> _resumeMenu;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	explicit PauseScreen(const std::function<void()>& resumeMenu, const std::function<void()>& closeMenu);

	void setText(const sf::String& text);

	void handleEvent(const sf::Event&) override;
};
