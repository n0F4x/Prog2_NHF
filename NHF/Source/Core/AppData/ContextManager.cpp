#include "ContextManager.hpp"

#include <algorithm>


static const std::map<const sf::Keyboard::Key, const std::string> _validKeys{
		{ sf::Keyboard::A, "A" },
		{ sf::Keyboard::B, "B" },
		{ sf::Keyboard::C, "C" },
		{ sf::Keyboard::D, "D" },
		{ sf::Keyboard::E, "E" },
		{ sf::Keyboard::F, "F" },
		{ sf::Keyboard::G, "G" },
		{ sf::Keyboard::H, "H" },
		{ sf::Keyboard::I, "I" },
		{ sf::Keyboard::J, "J" },
		{ sf::Keyboard::K, "K" },
		{ sf::Keyboard::L, "L" },
		{ sf::Keyboard::M, "M" },
		{ sf::Keyboard::N, "N" },
		{ sf::Keyboard::O, "O" },
		{ sf::Keyboard::P, "P" },
		{ sf::Keyboard::Q, "Q" },
		{ sf::Keyboard::R, "R" },
		{ sf::Keyboard::S, "S" },
		{ sf::Keyboard::T, "T" },
		{ sf::Keyboard::U, "U" },
		{ sf::Keyboard::V, "V" },
		{ sf::Keyboard::W, "W" },
		{ sf::Keyboard::X, "X" },
		{ sf::Keyboard::Y, "Y" },
		{ sf::Keyboard::Z, "Z" },
		{ sf::Keyboard::Num0, "Num0" },
		{ sf::Keyboard::Num1, "Num1" },
		{ sf::Keyboard::Num2, "Num2" },
		{ sf::Keyboard::Num3, "Num3" },
		{ sf::Keyboard::Num4, "Num4" },
		{ sf::Keyboard::Num5, "Num5" },
		{ sf::Keyboard::Num6, "Num6" },
		{ sf::Keyboard::Num7, "Num7" },
		{ sf::Keyboard::Num8, "Num8" },
		{ sf::Keyboard::Num9, "Num9" },
		{ sf::Keyboard::Space, "Space" },
		{ sf::Keyboard::Tab, "Tab" },
		{ sf::Keyboard::Left, "Left" },
		{ sf::Keyboard::Right, "Right" },
		{ sf::Keyboard::Up, "Up" },
		{ sf::Keyboard::Down, "Down" }
};
static const std::vector<int> _validPlatformCounts{ 3, 4, 5, 6, 7, 8 };

static bool isValidKey(const sf::Event::KeyEvent& keyEvent) {
	return _validKeys.contains(keyEvent.code);
}
static bool isValidPlatformCount(const int& count) {
	return std::ranges::any_of(_validPlatformCounts, [count](auto elem) { return elem == count; });
}


template <typename T>
class Validator : public Context::ValidatorBase {
public:
	explicit Validator<T>(const std::function<bool(const T&)>& func = [](const T&) -> bool { return true; }) : Context::ValidatorBase{
		[func](const std::any& val) -> bool {
			T casted;
			try {
				casted = std::any_cast<T>(val);
			}
			catch (const std::bad_any_cast&) {
				return false;
			}
			return func(casted);
		}
	} {}
};
template class Validator<sf::Event::KeyEvent>;
template class Validator<int>;
template class Validator<PlatformControl>;


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


void ContextManager::addContext(const std::string& name, const std::any& initialValue, Context::ValidatorBase* validator, const ToStringConverter& converter) {
	_contexts.try_emplace(name, initialValue, validator, converter);
}


ContextManager::ContextManager() {
	addContext("jumpKey", sf::Event::KeyEvent{ sf::Keyboard::Space }, new Validator<sf::Event::KeyEvent>{isValidKey}, KeyConverter{});
	addContext("platformCount", 3, new Validator<int>{isValidPlatformCount}, IntConverter{});
	addContext("platformControl", PlatformControl::Keyboard, new Validator<PlatformControl>{}, PCConverter{});
	addContext("switchKey1", sf::Event::KeyEvent{ sf::Keyboard::Left }, new Validator<sf::Event::KeyEvent>{isValidKey}, KeyConverter{});
	addContext("switchKey2", sf::Event::KeyEvent{ sf::Keyboard::Right }, new Validator<sf::Event::KeyEvent>{isValidKey}, KeyConverter{});
}



bool operator==(const sf::Event::KeyEvent& lhs, const sf::Event::KeyEvent& rhs) {
	return
		lhs.alt == rhs.alt &&
		lhs.code == rhs.code &&
		lhs.control == rhs.control &&
		lhs.shift == rhs.shift &&
		lhs.system == rhs.system;
}

