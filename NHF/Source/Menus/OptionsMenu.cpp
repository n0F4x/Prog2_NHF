#include "OptionsMenu.hpp"

#include "../GUI/Widgets/Button.hpp"
#include "../GUI/Widgets/Text.hpp"
#include "../GUI//Widgets/Bar.hpp"
#include "../GUI/Widgets/InputField.hpp"
#include "../GUI/Theme.hpp"


OptionsMenu::OptionsMenu() {
	// Widget height
	Text tmp{ "Tmp", AppData::assets.getFont("Dameron"), 56u };

	// Construct "Back" button
	Button* backButton = new Button{ "Back", AppData::assets.getFont("Dameron"), 76u, [this]() {Menu::close(); } };
	backButton->setPosition({ Window::getSize().x / 40.f, Window::getSize().x / 40.f });
	addMenuItem(std::unique_ptr<Button>{backButton});

	// Construct "Options" text
	Text* title = new Text{ "OPTIONS", AppData::assets.getFont("The Wireframe"), 132u };
	title->setPosition({ Window::getSize().x / 2.f - title->getSize().x / 2.f, (Window::getSize().y - 11.f * tmp.getSize().y * 2.f) / 4.f - title->getSize().y / 2.f });
	title->setFillColor(theme::Secondary);
	addMenuItem(std::unique_ptr<Text>{title});

	// Construct "Lane Count" bar and label
	auto* LCbar = new Bar<int>{
		Window::getSize().x * 0.6f, {"3", "4", "5", "6", "7", "8"}, AppData::assets.getFont("Dameron"), 56u,
		[](const int& amount) -> bool { return AppData::context.setPlatformCount(amount); },
		[]() -> std::string {
			return AppData::context.getPlatformCount().second;
		}
	};
	LCbar->center(Window::getLocalBounds());
	LCbar->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - LCbar->getSize().x) / 2.f, LCbar->getPosition().y });
	LCbar->move({ 0.f, -3 * LCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar<int>>{LCbar});
	Text* LClabel = new Text{ "Lane Count:", AppData::assets.getFont("Dameron"), 56u };
	LClabel->center(Window::getLocalBounds());
	LClabel->move({ -1.f * Window::getSize().x / 2.f + LClabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	LClabel->move({ 0.f, -3 * LCbar->getSize().y });
	LClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(LClabel));

	// Construct "Jump Key" input field and label
	InputField* JKinput = new InputField{
		AppData::assets.getFont("Dameron"), 56u,
		[](const sf::Event::KeyEvent& keyEvent) -> bool { return AppData::context.setJumpKey(keyEvent); },
		[]() -> std::string {
			return AppData::context.getJumpKey().second;
		}
	};
	JKinput->center(Window::getLocalBounds());
	JKinput->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - JKinput->getSize().x) / 2.f, JKinput->getPosition().y });
	JKinput->move({ 0.f, -1.f * JKinput->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(JKinput));
	Text* JKlabel = new Text{ "Jump Key:", AppData::assets.getFont("Dameron"), 56u };
	JKlabel->center(Window::getLocalBounds());
	JKlabel->move({ -1.f * Window::getSize().x / 2.f + JKlabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	JKlabel->move({ 0.f, -1.f * JKinput->getSize().y });
	JKlabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(JKlabel));

	// Construct "Platfrom Control" bar and label
	auto* PCbar = new Bar<PlatformControl>{
		Window::getSize().x * 0.6f, {"Keyboard", "Mouse"}, AppData::assets.getFont("Dameron"), 56u,
		[](const PlatformControl& control) -> bool { return AppData::context.setPlatformControl(control); } ,
		[]() -> std::string {
			return AppData::context.getPlatformControl().second;
		}
	};
	PCbar->center(Window::getLocalBounds());
	PCbar->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - PCbar->getSize().x) / 2.f, PCbar->getPosition().y });
	PCbar->move({ 0.f, +1.f * PCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar<PlatformControl>>{PCbar});
	Text* PClabel = new Text{ "Control Mode:", AppData::assets.getFont("Dameron"), 56u };
	PClabel->center(Window::getLocalBounds());
	PClabel->move({ -1.f * Window::getSize().x / 2.f + PClabel->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	PClabel->move({ 0.f, +1.f * PCbar->getSize().y });
	PClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(PClabel));

	// Construct "Switch Key 1" input field and label
	InputField* SK1input = new InputField{ 
		AppData::assets.getFont("Dameron"), 56u,
		[](const sf::Event::KeyEvent& keyEvent) -> bool { AppData::context.setSwitchKey1(keyEvent); },
		[]() -> std::string {
			return AppData::context.getSwitchKey1().second;
		} 
	};
	SK1input->center(Window::getLocalBounds());
	SK1input->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - SK1input->getSize().x) / 2.f, SK1input->getPosition().y });
	SK1input->move({ 0.f, +3.f * SK1input->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(SK1input));
	Text* SK1label = new Text{ "Switch Key 1:", AppData::assets.getFont("Dameron"), 56u };
	SK1label->center(Window::getLocalBounds());
	SK1label->move({ -1.f * Window::getSize().x / 2.f + SK1label->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	SK1label->move({ 0.f, +3.f * SK1input->getSize().y });
	SK1label->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(SK1label));

	// Construct "Switch Key 2" input field and label
	InputField* SK2input = new InputField{
		AppData::assets.getFont("Dameron"), 56u,
		[](const sf::Event::KeyEvent& keyEvent) -> bool { AppData::context.setSwitchKey2(keyEvent); },
		[]() -> std::string {
			return AppData::context.getSwitchKey2().second;
		}
	};
	SK2input->center(Window::getLocalBounds());
	SK2input->setPosition({ Window::getSize().x / 3.f + (Window::getSize().x / 3.f * 2.f - SK2input->getSize().x) / 2.f, SK2input->getPosition().y });
	SK2input->move({ 0.f, +5.f * SK2input->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(SK2input));
	Text* SK2label = new Text{ "Switch Key 2:", AppData::assets.getFont("Dameron"), 56u };
	SK2label->center(Window::getLocalBounds());
	SK2label->move({ -1.f * Window::getSize().x / 2.f + SK2label->getSize().x / 2.f + Window::getSize().x / 40.f, 0.f });
	SK2label->move({ 0.f, +5.f * SK2input->getSize().y });
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