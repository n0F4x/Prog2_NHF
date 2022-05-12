#include "ContextManager.hpp"

#include <algorithm>
#include <iostream>
#include <fstream> 


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
static const std::vector<int> _validLaneCounts{ 3, 4, 5, 6, 7, 8 };


// Validator functions
static bool isValidKey(const std::any& keyEvent) {
	return _validKeys.contains(std::any_cast<sf::Event::KeyEvent>(keyEvent).code);
}
static bool isValidLaneCount(const std::any& count) {
	return std::ranges::any_of(_validLaneCounts, [count](auto elem) { return elem == std::any_cast<int>(count); });
}


// ToStringConverters
class BoolConverter : public Context::ToStringConverter {
public:
	BoolConverter() : Context::ToStringConverter{
		[](const std::any& val) -> std::string { return std::any_cast<bool>(val) ? "On" : "Off"; }
	} {}
};
class IntConverter : public Context::ToStringConverter {
public:
	IntConverter() : Context::ToStringConverter{
		[](const std::any& val) -> std::string { return std::to_string(std::any_cast<int>(val)); }
	} {}
};
class KeyConverter : public Context::ToStringConverter {
public:
	KeyConverter() : Context::ToStringConverter{
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
class PCConverter : public Context::ToStringConverter {
public:
	PCConverter() : Context::ToStringConverter{
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


void ContextManager::addContext(
	const std::string& name,
	const std::any& initialValue,
	const Context::ToStringConverter& converter,
	const Context::Validator& validator
) {
	_contexts.try_emplace(name, initialValue, converter, validator);
}


ContextManager::ContextManager() {
	addContext("jumpKey", sf::Event::KeyEvent{ sf::Keyboard::Space }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("laneCount", 8, IntConverter{}, Context::Validator{ isValidLaneCount });
	addContext("platformControl", PlatformControl::Keyboard, PCConverter{});
	addContext("switchKey1", sf::Event::KeyEvent{ sf::Keyboard::Left }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("switchKey2", sf::Event::KeyEvent{ sf::Keyboard::Right }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("holdSwitch", false, BoolConverter{});
}


void ContextManager::loadFromFile() {
	find("laneCount")->set(3);	/* Re - initialization */


	std::ifstream file("./Config/contexts.ini");
	if (!file) {
		return;
	}
	
	// Read jumpKey
	sf::Event::KeyEvent jumpKey;
	std::string buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	for (const auto& [key, value] : _validKeys) {
		if (value == buffer) {
			jumpKey.code = key;
		}
	}
	file >> buffer;
	buffer == "true" ? jumpKey.alt = true : jumpKey.alt = false;
	file >> buffer;
	buffer == "true" ? jumpKey.control = true : jumpKey.control = false;
	file >> buffer;
	buffer == "true" ? jumpKey.shift = true : jumpKey.shift = false;
	file >> buffer;
	buffer == "true" ? jumpKey.system = true : jumpKey.system = false;
}


Context* ContextManager::find(const std::string_view& name) {
	if (auto it = _contexts.find(name); it != _contexts.end()) {
		return &it->second;
	}
	return nullptr;
}



bool operator==(const sf::Event::KeyEvent& lhs, const sf::Event::KeyEvent& rhs) {
	return
		lhs.alt == rhs.alt &&
		lhs.code == rhs.code &&
		lhs.control == rhs.control &&
		lhs.shift == rhs.shift &&
		lhs.system == rhs.system;
}

