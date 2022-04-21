#include "OptionsMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI//Widgets/Bar.hpp"
#include "../GUI/Widgets/InputField.hpp"
#include "../GUI/Theme.hpp"


OptionsMenu::OptionsMenu() {
	// Widget height
	Text tmp{ "Tmp", AppData::assets.getFont("Dameron"), 56u };

	// Construct "Options" text
	Text* text = new Text{ "OPTIONS", AppData::assets.getFont("The Wireframe"), 132u };
	text->setPosition({ Window::getSize().x / 2.f, (Window::getSize().y - 11.f * tmp.getSize().y * 2.f) / 4.f });
	text->setFillColor(theme::Secondary);
	addMenuItem(std::unique_ptr<Text>{text});

	// Construct "Lane Count" bar and label
	Bar* LCbar = new Bar{
		Window::getSize().x * 0.6f, {"3", "4", "5", "6", "7", "8"}, AppData::assets.getFont("Dameron"), 56u,
		AppData::context.setPlatformCount, [&]() -> std::string {
			return AppData::context.getPlatformCount().second;
		}
	};
	LCbar->center(Window::getSize());
	LCbar->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - LCbar->getSize().x) / 2.f, LCbar->getPosition().y });
	LCbar->move({ 0.f, -4 * LCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar>{LCbar});
	Text* LClabel = new Text{ "Lane Count:", AppData::assets.getFont("Dameron"), 56u };
	LClabel->center(Window::getSize());
	LClabel->move({ -1.f * Window::getSize().x / 2.f + LClabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	LClabel->move({ 0.f, -4 * LCbar->getSize().y });
	LClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(LClabel));

	// Construct "Jump Key" input field and label
	InputField* JKinput = new InputField{ AppData::assets.getFont("Dameron"), 56u, AppData::context.setJumpKey, [&]() -> std::string {
		return AppData::context.getPlatformControl().second;
	} };
	JKinput->center(Window::getSize());
	JKinput->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - JKinput->getSize().x) / 2.f, JKinput->getPosition().y });
	JKinput->move({ 0.f, -2.f * JKinput->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(JKinput));
	Text* JKlabel = new Text{ "Jump Key:", AppData::assets.getFont("Dameron"), 56u };
	JKlabel->center(Window::getSize());
	JKlabel->move({ -1.f * Window::getSize().x / 2.f + JKlabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	JKlabel->move({ 0.f, -2.f * JKinput->getSize().y });
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
	PCbar->move({ 0.f, 0.f * PCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar>{PCbar});
	Text* PClabel = new Text{ "Control Mode:", AppData::assets.getFont("Dameron"), 56u };
	PClabel->center(Window::getSize());
	PClabel->move({ -1.f * Window::getSize().x / 2.f + PClabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	PClabel->move({ 0.f, 0.f * PCbar->getSize().y });
	PClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(PClabel));

	// Construct "Switch Key 1" input field and label
	InputField* SK1input = new InputField{ AppData::assets.getFont("Dameron"), 56u, AppData::context.setSwitchKey1, [&]() -> std::string {
		return AppData::context.getSwitchKey1().second;
	} };
	SK1input->center(Window::getSize());
	SK1input->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - SK1input->getSize().x) / 2.f, SK1input->getPosition().y });
	SK1input->move({ 0.f, +2.f * SK1input->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(SK1input));
	Text* SK1label = new Text{ "Switch Key 1:", AppData::assets.getFont("Dameron"), 56u };
	SK1label->center(Window::getSize());
	SK1label->move({ -1.f * Window::getSize().x / 2.f + SK1label->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	SK1label->move({ 0.f, +2.f * SK1input->getSize().y });
	SK1label->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(SK1label));

	// Construct "Switch Key 2" input field and label
	InputField* SK2input = new InputField{ AppData::assets.getFont("Dameron"), 56u, AppData::context.setSwitchKey2, [&]() -> std::string {
		return AppData::context.getSwitchKey2().second;
	} };
	SK2input->center(Window::getSize());
	SK2input->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - SK2input->getSize().x) / 2.f, SK2input->getPosition().y });
	SK2input->move({ 0.f, +4.f * SK2input->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(SK2input));
	Text* SK2label = new Text{ "Switch Key 2:", AppData::assets.getFont("Dameron"), 56u };
	SK2label->center(Window::getSize());
	SK2label->move({ -1.f * Window::getSize().x / 2.f + SK2label->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	SK2label->move({ 0.f, +4.f * SK2input->getSize().y });
	SK2label->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(SK2label));
}

void OptionsMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			Menu::close();
		}
	}
}