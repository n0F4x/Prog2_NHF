#include "ContextManager.hpp"

#include <algorithm>


// Validator helpers
static const std::map<const sf::Keyboard::Key, const std::string> _validKeys{
		{ sf::Keyboard::Key::A, "A" },
		{ sf::Keyboard::Key::B, "B" },
		{ sf::Keyboard::Key::C, "C" },
		{ sf::Keyboard::Key::D, "D" },
		{ sf::Keyboard::Key::E, "E" },
		{ sf::Keyboard::Key::F, "F" },
		{ sf::Keyboard::Key::G, "G" },
		{ sf::Keyboard::Key::H, "H" },
		{ sf::Keyboard::Key::I, "I" },
		{ sf::Keyboard::Key::J, "J" },
		{ sf::Keyboard::Key::K, "K" },
		{ sf::Keyboard::Key::L, "L" },
		{ sf::Keyboard::Key::M, "M" },
		{ sf::Keyboard::Key::N, "N" },
		{ sf::Keyboard::Key::O, "O" },
		{ sf::Keyboard::Key::P, "P" },
		{ sf::Keyboard::Key::Q, "Q" },
		{ sf::Keyboard::Key::R, "R" },
		{ sf::Keyboard::Key::S, "S" },
		{ sf::Keyboard::Key::T, "T" },
		{ sf::Keyboard::Key::U, "U" },
		{ sf::Keyboard::Key::V, "V" },
		{ sf::Keyboard::Key::W, "W" },
		{ sf::Keyboard::Key::X, "X" },
		{ sf::Keyboard::Key::Y, "Y" },
		{ sf::Keyboard::Key::Z, "Z" },
		{ sf::Keyboard::Key::Num0, "Num0" },
		{ sf::Keyboard::Key::Num1, "Num1" },
		{ sf::Keyboard::Key::Num2, "Num2" },
		{ sf::Keyboard::Key::Num3, "Num3" },
		{ sf::Keyboard::Key::Num4, "Num4" },
		{ sf::Keyboard::Key::Num5, "Num5" },
		{ sf::Keyboard::Key::Num6, "Num6" },
		{ sf::Keyboard::Key::Num7, "Num7" },
		{ sf::Keyboard::Key::Num8, "Num8" },
		{ sf::Keyboard::Key::Num9, "Num9" },
		{ sf::Keyboard::Key::Space, "Space" },
		{ sf::Keyboard::Key::Tab, "Tab" },
		{ sf::Keyboard::Key::Left, "Left" },
		{ sf::Keyboard::Key::Right, "Right" },
		{ sf::Keyboard::Key::Up, "Up" },
		{ sf::Keyboard::Key::Down, "Down" }
};
static const std::vector<int> _validPlatformCounts{ 3, 4, 5, 6, 7, 8 };


// Validator functions
static bool isValidKey(const std::any& keyEvent) {
	return _validKeys.contains(std::any_cast<sf::Event::KeyEvent>(keyEvent).code);
}
static bool isValidPlatformCount(const std::any& count) {
	return std::ranges::any_of(_validPlatformCounts, [count](auto elem) { return elem == std::any_cast<int>(count); });
}


// ToStringConverters
class BoolConverter : public ToStringConverter {
public:
	BoolConverter() : ToStringConverter{
		[](const std::any& val) -> std::string { return std::any_cast<bool>(val) ? "true" : "false"; }
	} {}
};
class IntConverter : public ToStringConverter {
public:
	IntConverter() : ToStringConverter{
		[](const std::any& val) -> std::string { return std::to_string(std::any_cast<int>(val)); }
	} {}
};
class KeyConverter : public ToStringConverter {
public:
	KeyConverter() : ToStringConverter{
		[](const std::any& val) -> std::string {
			sf::Event::KeyEvent key = std::any_cast<sf::Event::KeyEvent>(val);
			std::string string = "";
			if (key.control) {
				string.append("Ctrl+");
			}
			if (key.alt) {
				string.append("Alt+");
			}
			if (key.shift) {
				string.append("Shift+");
			}
			string.append(_validKeys.at(key.code));
			return string;
		}
	} {}
};
class PCConverter : public ToStringConverter {
public:
	PCConverter() : ToStringConverter{
		[](const std::any& val) -> std::string {
			switch (std::any_cast<PlatformControl>(val)) {
			case PlatformControl::Keyboard:
				return "KeyBoard";
			case PlatformControl::Mouse:
				return "Mouse";
			default:
				return "Invalid PlatformControl";
			}
		}
	} {}
};


void ContextManager::addContext(const std::string& name, const std::any& initialValue, const ToStringConverter& converter, const Context::Validator& validator) {
	_contexts.try_emplace(name, initialValue, converter, validator);
}


ContextManager::ContextManager() {
	addContext("jumpKey", sf::Event::KeyEvent{ sf::Keyboard::Space }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("platformCount", 3, IntConverter{}, Context::Validator{ isValidPlatformCount });
	addContext("platformControl", PlatformControl::Keyboard, PCConverter{});
	addContext("switchKey1", sf::Event::KeyEvent{ sf::Keyboard::Left }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("switchKey2", sf::Event::KeyEvent{ sf::Keyboard::Right }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("holdSwitch", false, BoolConverter{});
}



bool operator==(const sf::Event::KeyEvent& lhs, const sf::Event::KeyEvent& rhs) {
	return
		lhs.alt == rhs.alt &&
		lhs.code == rhs.code &&
		lhs.control == rhs.control &&
		lhs.shift == rhs.shift &&
		lhs.system == rhs.system;
}

