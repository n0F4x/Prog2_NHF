#include "ContextManager.hpp"

#include <algorithm>
#include <fstream>
#include <exception>
#include <iostream>


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
	return std::ranges::any_of(_validLaneCounts, [count](auto elem) { return elem == std::any_cast<unsigned>(count); });
}


// ToStringConverters
class BoolConverter : public Context::ToStringConverter {
public:
	BoolConverter() : Context::ToStringConverter{
		[](const std::any& val) -> std::string { return std::any_cast<bool>(val) ? "On" : "Off"; }
	} {}
};
class UnsignedConverter : public Context::ToStringConverter {
public:
	UnsignedConverter() : Context::ToStringConverter{
		[](const std::any& val) -> std::string { return std::to_string(std::any_cast<unsigned>(val)); }
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
				return "Keyboard";
			case PlatformControl::Mouse:
				return "Mouse";
			default:
				return "Invalid PlatformControl";
			}
		}
	} {}
};
class SpeedConverter : public Context::ToStringConverter {
public:
	SpeedConverter() : Context::ToStringConverter{
		[](const std::any& val) -> std::string {
			if (auto _val = std::any_cast<unsigned>(val); _val == 40u) {
				return "Slow";
			}
			else if (_val == 20u) {
				return "Avg";
			}
			else if (_val == 15u) {
				return "Fast";
			}
			else if (_val == 10u) {
				return "Pro";
			}
			else if (_val <= 7u) {
				return "Seer";
			}
			return "error";
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
	addContext("laneCount", 3u, UnsignedConverter{}, Context::Validator{ isValidLaneCount });
	addContext("speed", 20u, SpeedConverter{});
	addContext("platformControl", PlatformControl::Keyboard, PCConverter{});
	addContext("jumpKey", sf::Event::KeyEvent{ sf::Keyboard::Space }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("switchKey1", sf::Event::KeyEvent{ sf::Keyboard::Left }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("switchKey2", sf::Event::KeyEvent{ sf::Keyboard::Right }, KeyConverter{}, Context::Validator{ isValidKey });
	addContext("holdSwitch", false, BoolConverter{});
}


sf::Event::KeyEvent readKey(std::ifstream& file) {
	sf::Event::KeyEvent key;
	std::string buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	for (const auto& [it_key, it_value] : _validKeys) {
		if (it_value == buffer) {
			key.code = it_key;
		}
	}
	file >> buffer;
	key.alt = buffer == "true";
	file >> buffer;
	key.control = buffer == "true";
	file >> buffer;
	key.shift = buffer == "true";
	file >> buffer;
	return key;
}

unsigned readUnsigned(std::ifstream& file) {
	std::string buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	unsigned res = std::stoi(buffer);
	file >> buffer;
	return res;
}

PlatformControl readPlatformControl(std::ifstream& file) {
	std::string buffer;
	PlatformControl res = PlatformControl::Keyboard;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	if (buffer == "Keyboard") {
		res = PlatformControl::Keyboard;
	}
	else if (buffer == "Mouse") {
		res = PlatformControl::Mouse;
	}
	file >> buffer;
	return res;
}

bool readBool(std::ifstream& file) {
	std::string buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	bool res = buffer == "true";
	file >> buffer;
	return res;
}

unsigned readSpeed(std::ifstream& file) {
	std::string buffer;
	unsigned res = 20u;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	file >> buffer;
	if (buffer == "Slow") {
		res = 40u;
	}
	else if (buffer == "Avg") {
		res = 20u;
	}
	else if (buffer == "Fast") {
		res = 15u;
	}
	else if (buffer == "Pro") {
		res = 10u;
	}
	else if (buffer == "Seer") {
		res = 6u;
	}
	file >> buffer;
	return res;
}

void ContextManager::loadFromFile() {
	std::ifstream file("./Config/contexts.ini");
	if (file) {
		try {
			std::string buffer;
			buffer.resize(31);
			file.getline(buffer.data(), 30);
			file.getline(buffer.data(), 30);
			find("laneCount")->set(readUnsigned(file));
			find("speed")->set(readSpeed(file));
			find("platformControl")->set(readPlatformControl(file));
			find("jumpKey")->set(readKey(file));
			find("switchKey1")->set(readKey(file));
			find("switchKey2")->set(readKey(file));
			find("holdSwitch")->set(readBool(file));
			file.close();
		}
		catch (const std::invalid_argument&) {
			std::cerr << "Error reading file(contexts.ini) - Inadequate file format\n";
		}
	}
}


void writeBasic(std::ofstream& file, const std::string_view& name, const Context& context) {
	file << '\n' << name << " = {\n\t" << context.string() << "\n}\n";
}

void writeKey(std::ofstream& file, const std::string_view& name, const Context& context) {
	std::string string = context.string();
	std::string code;
	for (auto letter = string.rbegin(); letter != string.rend() && *letter != '+'; letter++) {
		code += *letter;
	}
	std::ranges::reverse(code);
	sf::Event::KeyEvent key = context.get<sf::Event::KeyEvent>();
	file << std::boolalpha;
	file << '\n' << name << " = {\n\t";
	file << code;
	file << "\n\t" << key.alt << "\n\t" << key.control << "\n\t" << key.shift << "\n}\n";
	file << std::noboolalpha;
}

void writeBool(std::ofstream& file, const std::string_view& name, const Context& context) {
	file << std::boolalpha;
	file << '\n' << name << " = {\n\t" << context.get<bool>() << "\n}\n";
	file << std::noboolalpha;
}

void ContextManager::save() {
	std::ofstream file("./Config/contexts.ini");
	if (file) {
		file << "# Don't touch this!\n";

		writeBasic(file, "laneCount", *find("laneCount"));
		writeBasic(file, "speed", *find("speed"));
		writeBasic(file, "platformControl", *find("platformControl"));
		writeKey(file, "jumpKey", *find("jumpKey"));
		writeKey(file, "switchKey1", *find("switchKey1"));
		writeKey(file, "switchKey2", *find("switchKey2"));
		writeBool(file, "holdSwitch", *find("holdSwitch"));
		file.close();
	}
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

