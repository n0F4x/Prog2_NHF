#include "../MenuItem.hpp"

#include "../../GUI/Widgets/Text.hpp"
#include "../../GUI/Widgets/Button.hpp"


/**
 * @brief	Class for displaying and managing the pause screen filter inside the game menu
*/
class PauseScreen : public MenuItem {
private:
	sf::RectangleShape _bg{Window::getSize()};
	Text _text{ "Resume", AppData::getFont("Dameron"), 84u };
	Button _backButton;
	Button _playAgainButton;

	const std::function<void()> _resumeMenu;

	bool _gameOver = false;

	/**
	 * @brief	Renders filter to target
	 * @param target	The render target
	 * @param states	The render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	/**
	 * @brief	Constructs new PauseScreen 
	 * @param resumeMenu	Function that resumes the (game) menu
	 * @param closeMenu		Function that closes the (game) menu
	 * @param initMenu		Function that initiates the (game) menu
	*/
	explicit PauseScreen(const std::function<void()>& resumeMenu, const std::function<void()>& closeMenu, const std::function<void()>& initMenu);

	/**
	 * @brief	Changes the PauseScreen to reflect an end of game filter
	*/
	void gameOver();
	/**
	 * @brief	Handles user input
	 * @param event	User input
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Initiates PauseScreen
	*/
	void init() override;
};
