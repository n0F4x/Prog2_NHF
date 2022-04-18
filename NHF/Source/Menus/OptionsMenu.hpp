#include "Menu.hpp"


class OptionsMenu : public Menu {
public:
	OptionsMenu();

	void handleEvent(const sf::Event& event) override;
};
