#include "OptionsMenu.hpp"

#include "../GUI/Widgets/Text.hpp"
#include "../GUI//Widgets/Bar.hpp"
#include "../GUI/Widgets/InputField.hpp"
#include "../GUI/Theme.hpp"


OptionsMenu::OptionsMenu() {
	// Construct "Options" text
	Text* text = new Text{ "OPTIONS", _appData.assets.getFont("The Wireframe"), 66u };
	text->center(_window.getSize());
	text->move({ 0.f, -1.f * _window.getSize().y / 2.f + text->getSize().y * 2.f });
	text->setFillColor(theme::Purple);
	addMenuItem(std::unique_ptr<Text>{text});

	// Construct "Lane Count" bar and label
	Bar* LCbar = new Bar{
		_window.getSize().x * 0.6f, {"3", "4", "5", "6", "7", "8"}, _appData.assets.getFont("Dameron"), 56u,
		&_appData.context.setPlatformCount, [&]() -> std::string {
			return _appData.context.getPlatformCount().second;
		}
	};
	LCbar->center(_window.getSize());
	LCbar->setPosition({ _window.getSize().x / 3.f + (_window.getSize().x / 3.f * 2.f - LCbar->getSize().x) / 2.f, LCbar->getPosition().y });
	LCbar->move({ 0.f, -2 * LCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar>{LCbar});
	Text* LClabel = new Text{ "Lane Count:", _appData.assets.getFont("Dameron"), 56u };
	LClabel->center(_window.getSize());
	LClabel->move({ -1.f * _window.getSize().x / 2.f + LClabel->getSize().x / 2.f + _window.getSize().x / 40.f, 0.f });
	LClabel->move({ 0.f, -2 * LCbar->getSize().y });
	LClabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(LClabel));

	// Construct "Jump Key" input field and label
	InputField* JKinput = new InputField{ _appData.context.getJumpKey().second, _appData.assets.getFont("Dameron"), 56u, [&](const sf::Event::KeyEvent& event, std::string& string) -> bool {
		bool res = _appData.context.setJumpKey(event);
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
			string.append(_appData.context.getJumpKey().second);
		}
		return !res;
	} };
	JKinput->center(_window.getSize());
	JKinput->setPosition({ _window.getSize().x / 3.f + (_window.getSize().x / 3.f * 2.f - JKinput->getSize().x) / 2.f, JKinput->getPosition().y });
	JKinput->move({ 0.f, 0.f * JKinput->getSize().y });
	addMenuItem(std::unique_ptr<InputField>(JKinput));
	Text* JKlabel = new Text{ "Jump Key:", _appData.assets.getFont("Dameron"), 56u };
	JKlabel->center(_window.getSize());
	JKlabel->move({ -1.f * _window.getSize().x / 2.f + JKlabel->getSize().x / 2.f + _window.getSize().x / 40.f, 0.f });
	JKlabel->move({ 0.f, 0.f * JKinput->getSize().y });
	JKlabel->setFillColor(theme::IndigoPurple);
	addMenuItem(std::unique_ptr<Text>(JKlabel));

	// Construct "Platfrom Control" bar and label
	Bar* PCbar = new Bar{
		_window.getSize().x * 0.6f, {"Keyboard", "Mouse"}, _appData.assets.getFont("Dameron"), 56u,
		_appData.context.setPlatformControl, [&]() -> std::string {
			return _appData.context.getPlatformControl().second;
		}
	};
	PCbar->center(_window.getSize());
	PCbar->setPosition({ _window.getSize().x / 3.f + (_window.getSize().x / 3.f * 2.f - PCbar->getSize().x) / 2.f, PCbar->getPosition().y });
	PCbar->move({ 0.f, 2 * PCbar->getSize().y });
	addMenuItem(std::unique_ptr<Bar>{PCbar});
	Text* PClabel = new Text{ "Control:", _appData.assets.getFont("Dameron"), 56u };
	PClabel->center(_window.getSize());
	PClabel->move({ -1.f * _window.getSize().x / 2.f + PClabel->getSize().x / 2.f + _window.getSize().x / 40.f, 0.f });
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