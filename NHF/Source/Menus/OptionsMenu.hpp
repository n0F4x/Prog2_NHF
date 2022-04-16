#include "Menu.hpp"

#include "../AppData/AppData.hpp"


class OptionsMenu : public Menu {
public:
	OptionsMenu(AppData& appData);

	void handleEvent(const sf::Event& event) override;
};