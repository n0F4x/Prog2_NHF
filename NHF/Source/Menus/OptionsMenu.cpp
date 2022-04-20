#include "OptionsMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI//Widgets/Bar.hpp"
#include "../GUI/Widgets/InputField.hpp"
#include "../GUI/Theme.hpp"


OptionsMenu::OptionsMenu() {
	// Construct "Options" text
	Text* text = new Text{ "OPTIONS", AppData::assets.getFont("The Wireframe"), 66u };
	text->center(Window::getSize());
	text->move({ 0.f, -1.f * Window::getSize().y / 2.f + text->getSize().y * 2.f });
	text->setFillColor(theme::Purple);
	addMenuItem(std::unique_ptr<Text>{text});

	// Construct "Lane Count" bar and label
	Bar* LCbar = new Bar{
		Window::getSize().x * 0.6f, {"3", "4", "5", "6", "7", "8"}, AppData::assets.getFont("Dameron"), 56u,
		&AppData::context.setPlatformCount, [&]() -> std::string {
			return AppData::context.getPlatformCount().second;
		}
	};
	LCbar->center(Window::getSize());
	LCbar->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - LCbar->getSize().x) / 2.f, LCbar->getPosition().y });
	LCbar->move({ 0.f, -2 * LCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar>{LCbar});
	Text* LClabel = new Text{ "Lane Count:", AppData::assets.getFont("Dameron"), 56u };
	LClabel->center(Window::getSize());
	LClabel->move({ -1.f * Window::getSize().x / 2.f + LClabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	LClabel->move({ 0.f, -2 * LCbar->getSize().y });
	LClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(LClabel));

	// Construct "Jump Key" input field and label
	InputField* JKinput = new InputField{ AppData::context.getJumpKey().second, AppData::assets.getFont("Dameron"), 56u, [&](const sf::Event::KeyEvent& event, std::string& string) -> bool {
		bool res = AppData::context.setJumpKey(event);
		if (res) {
			string.clear();
			if (event.control) {
				string.append("Ctrl+");
			}
			if (event.alt) {
				string.append("Alt+");
			}
			if (event.shift) {
				string.append("Shift+");
			}
			string.append(AppData::context.getJumpKey().second);
		}
		return !res;
	} };
	JKinput->center(Window::getSize());
	JKinput->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - JKinput->getSize().x) / 2.f, JKinput->getPosition().y });
	JKinput->move({ 0.f, 0.f * JKinput->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(JKinput));
	Text* JKlabel = new Text{ "Jump Key:", AppData::assets.getFont("Dameron"), 56u };
	JKlabel->center(Window::getSize());
	JKlabel->move({ -1.f * Window::getSize().x / 2.f + JKlabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	JKlabel->move({ 0.f, 0.f * JKinput->getSize().y });
	JKlabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(JKlabel));

	// Construct "Platfrom Control" bar and label
	Bar* PCbar = new Bar{
		Window::getSize().x * 0.6f, {"Keyboard", "Mouse"}, AppData::assets.getFont("Dameron"), 56u,
		AppData::context.setPlatformControl, [&]() -> std::string {
			return AppData::context.getPlatformControl().second;
		}
	};
	PCbar->center(Window::getSize());
	PCbar->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - PCbar->getSize().x) / 2.f, PCbar->getPosition().y });
	PCbar->move({ 0.f, 2 * PCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar>{PCbar});
	Text* PClabel = new Text{ "Control:", AppData::assets.getFont("Dameron"), 56u };
	PClabel->center(Window::getSize());
	PClabel->move({ -1.f * Window::getSize().x / 2.f + PClabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	PClabel->move({ 0.f, 2 * PCbar->getSize().y });
	PClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(PClabel));
}

void OptionsMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			Menu::close();
		}
	}
}