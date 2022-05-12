#include "OptionsMenu.hpp"

#include "../GUI/Widgets/Button.hpp"
#include "../GUI/Widgets/Text.hpp"
#include "../GUI//Widgets/Bar.hpp"
#include "../GUI/Widgets/InputField.hpp"
#include "../GUI/Theme.hpp"


OptionsMenu::OptionsMenu() {
	// Widget size
	Text tmp{ "Ctrl+Alt+Shift+Space", AppData::getFont("Dameron"), 56u };

	// Construct "Back" button
	auto backButton = std::make_unique<Button>("Back", AppData::getFont("Dameron"), 76u, [this]() {close(); });
	backButton->setPosition({ Window::getSize().x / 40.f, Window::getSize().x / 40.f });

	// Construct "Options" text
	auto title = std::make_unique<Text>("OPTIONS", AppData::getFont("The Wireframe"), 96u);
	title->setPosition({
		Window::getSize().x / 2.f - title->getSize().x / 2.f,
		Window::getSize().x / 40.f
		});
	title->setFillColor(theme::Secondary);

	// Construct "Lane Count" bar and label
	std::vector<unsigned> LCcontents{ 3u, 4u, 5u, 6u, 7u, 8u };
	auto LCbar = std::make_unique<Bar<unsigned>>(tmp.getSize().x * 1.2f, LCcontents, AppData::getFont("Dameron"), 56u, "laneCount");
	LCbar->center(Window::getLocalBounds());
	LCbar->setPosition({
		Window::getSize().x / 5.f * 2.f + (Window::getSize().x / 5.f * 3.f - LCbar->getSize().x) / 2.f,
		LCbar->getPosition().y
		});
	LCbar->move({ 0.f, -5 * LCbar->getSize().y });
	auto LClabel = std::make_unique<Text>("Lane Count:", AppData::getFont("Dameron"), 56u);
	LClabel->center(Window::getLocalBounds());
	LClabel->setPosition({ Window::getSize().x - LCbar->getPosition().x - LCbar->getSize().x, LClabel->getPosition().y });
	LClabel->move({ 0.f, -5 * LCbar->getSize().y });
	LClabel->setFillColor(theme::IndigoPurple);

	// Construct "Jump Key" input field and label
	auto JKinput = std::make_unique<InputField>(AppData::getFont("Dameron"), 56u, "jumpKey");
	JKinput->center(Window::getLocalBounds());
	JKinput->setPosition({
		Window::getSize().x / 5.f * 2.f + (Window::getSize().x / 5.f * 3.f - JKinput->getSize().x) / 2.f,
		JKinput->getPosition().y
		});
	JKinput->move({ 0.f, -3.f * JKinput->getSize().y });
	auto JKlabel = std::make_unique<Text>("Jump Key:", AppData::getFont("Dameron"), 56u);
	JKlabel->center(Window::getLocalBounds());
	JKlabel->setPosition({ Window::getSize().x - JKinput->getPosition().x - JKinput->getSize().x, JKlabel->getPosition().y });
	JKlabel->move({ 0.f, -3.f * JKinput->getSize().y });
	JKlabel->setFillColor(theme::IndigoPurple);

	// Construct "Platfrom Control" bar and label
	std::vector<PlatformControl> PCcontents{ PlatformControl::Keyboard, PlatformControl::Mouse };
	auto PCbar = std::make_unique<Bar<PlatformControl>>(
		tmp.getSize().x * 1.2f, PCcontents, AppData::getFont("Dameron"), 56u, "platformControl"
		);
	PCbar->center(Window::getLocalBounds());
	PCbar->setPosition({
		Window::getSize().x / 5.f * 2.f + (Window::getSize().x / 5.f * 3.f - PCbar->getSize().x) / 2.f,
		PCbar->getPosition().y
		});
	PCbar->move({ 0.f, -1.f * PCbar->getSize().y });
	auto PClabel = std::make_unique<Text>("Control Mode:", AppData::getFont("Dameron"), 56u);
	PClabel->center(Window::getLocalBounds());
	PClabel->setPosition({ Window::getSize().x - PCbar->getPosition().x - PCbar->getSize().x, PClabel->getPosition().y });
	PClabel->move({ 0.f, -1.f * PCbar->getSize().y });
	PClabel->setFillColor(theme::IndigoPurple);

	// Construct "Switch Key 1" input field and label
	auto SK1input = std::make_unique<InputField>(AppData::getFont("Dameron"), 56u, "switchKey1");
	SK1input->center(Window::getLocalBounds());
	SK1input->setPosition({
		Window::getSize().x / 5.f * 2.f + (Window::getSize().x / 5.f * 3.f - SK1input->getSize().x) / 2.f,
		SK1input->getPosition().y
		});
	SK1input->move({ 0.f, +1.f * SK1input->getSize().y });
	auto SK1label = std::make_unique<Text>("Switch Key 1:", AppData::getFont("Dameron"), 56u);
	SK1label->center(Window::getLocalBounds());
	SK1label->setPosition({ Window::getSize().x - SK1input->getPosition().x - SK1input->getSize().x, SK1label->getPosition().y });
	SK1label->move({ 0.f, +1.f * SK1input->getSize().y });
	SK1label->setFillColor(theme::IndigoPurple);

	// Construct "Switch Key 2" input field and label
	auto SK2input = std::make_unique<InputField>(AppData::getFont("Dameron"), 56u, "switchKey2");
	SK2input->center(Window::getLocalBounds());
	SK2input->setPosition({
		Window::getSize().x / 5.f * 2.f + (Window::getSize().x / 5.f * 3.f - SK2input->getSize().x) / 2.f,
		SK2input->getPosition().y
		});
	SK2input->move({ 0.f, +3.f * SK2input->getSize().y });
	auto SK2label = std::make_unique<Text>("Switch Key 2:", AppData::getFont("Dameron"), 56u);
	SK2label->center(Window::getLocalBounds());
	SK2label->setPosition({ Window::getSize().x - SK2input->getPosition().x - SK2input->getSize().x, SK2label->getPosition().y });
	SK2label->move({ 0.f, +3.f * SK2input->getSize().y });
	SK2label->setFillColor(theme::IndigoPurple);

	// Construct "Hold Switch" bar and label
	std::vector<bool> HScontents{ false, true };
	auto HSbar = std::make_unique<Bar<bool>>(tmp.getSize().x * 1.2f, HScontents, AppData::getFont("Dameron"), 56u, "holdSwitch");
	HSbar->center(Window::getLocalBounds());
	HSbar->setPosition({
		Window::getSize().x / 5.f * 2.f + (Window::getSize().x / 5.f * 3.f - HSbar->getSize().x) / 2.f,
		HSbar->getPosition().y
		});
	HSbar->move({ 0.f, +5.f * HSbar->getSize().y });
	auto HSlabel = std::make_unique<Text>("Hold Switch:", AppData::getFont("Dameron"), 56u);
	HSlabel->center(Window::getLocalBounds());
	HSlabel->setPosition({ Window::getSize().x - HSbar->getPosition().x - HSbar->getSize().x, HSlabel->getPosition().y });
	HSlabel->move({ 0.f, +5.f * HSbar->getSize().y });
	HSlabel->setFillColor(theme::IndigoPurple);

	// Construct "Speed" bar and label
	std::vector<unsigned> Pcontents{ 30u, 20u, 15u, 10u };
	auto Sbar = std::make_unique<Bar<unsigned>>(tmp.getSize().x * 1.2f, Pcontents, AppData::getFont("Dameron"), 56u, "speed");
	Sbar->center(Window::getLocalBounds());
	Sbar->setPosition({
		Window::getSize().x / 5.f * 2.f + (Window::getSize().x / 5.f * 3.f - Sbar->getSize().x) / 2.f,
		Sbar->getPosition().y
		});
	Sbar->move({ 0.f, +7.f * Sbar->getSize().y });
	auto Slabel = std::make_unique<Text>("Speed:", AppData::getFont("Dameron"), 56u);
	Slabel->center(Window::getLocalBounds());
	Slabel->setPosition({ Window::getSize().x - Sbar->getPosition().x - Sbar->getSize().x, Slabel->getPosition().y });
	Slabel->move({ 0.f, +7.f * Sbar->getSize().y });
	Slabel->setFillColor(theme::IndigoPurple);


	// Add items to Menu
	addMenuItem(std::move(backButton));
	addMenuItem(std::move(title));
	addMenuItem(std::move(LCbar));
	addMenuItem(std::move(LClabel));
	addMenuItem(std::move(JKinput));
	addMenuItem(std::move(JKlabel));
	addMenuItem(std::move(PCbar));
	addMenuItem(std::move(PClabel));
	addMenuItem(std::move(SK1input));
	addMenuItem(std::move(SK1label));
	addMenuItem(std::move(SK2input));
	addMenuItem(std::move(SK2label));
	addMenuItem(std::move(HSbar));
	addMenuItem(std::move(HSlabel));
	addMenuItem(std::move(Sbar));
	addMenuItem(std::move(Slabel));
}

void OptionsMenu::handleEvent(const sf::Event& event) {
	Menu::handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		close();
	}
}
