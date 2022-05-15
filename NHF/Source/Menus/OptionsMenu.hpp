#include "Menu.hpp"


/**
 * @brief	Class for managing and displaying the options menu of the application
*/
class OptionsMenu : public Menu {
public:
	/**
	 * @brief	Constructs new OptionsMenu
	*/
	OptionsMenu();

	/**
	 * @brief	Handles the user input inside the options menu
	 * @param event	The user input
	*/
	void handleEvent(const sf::Event& event) override;
};
