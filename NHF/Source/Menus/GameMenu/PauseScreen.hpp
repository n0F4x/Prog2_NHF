#include "../MenuItem.hpp"

#include "../../GUI/Widgets/Text.hpp"
#include "../../GUI/Widgets/Button.hpp"


class PauseScreen : public MenuItem {
private:
	sf::RectangleShape _bg{Window::getSize()};
	Text _text{ "Resume", AppData::getFont("Dameron"), 84u };
	Button _backButton;
	Button _playAgainButton;

	const std::function<void()> _resumeMenu;

	bool _gameOver = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	explicit PauseScreen(const std::function<void()>& resumeMenu, const std::function<void()>& closeMenu, const std::function<void()>& initMenu);

	void gameOver();

	void handleEvent(const sf::Event&) override;
	void init() override;
};
