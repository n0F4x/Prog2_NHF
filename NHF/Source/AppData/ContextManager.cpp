#include "ContextManager.hpp"


//namespace PlatformControl {
//	extern const int KeyBoard = 0;
//	extern const int Mouse = 1;
//}


sf::Event::KeyEvent ContextManager::_jumpKey = { sf::Keyboard::Space };
int ContextManager::_platformCount = 3;
PlatformControl ContextManager::_platformControl = PlatformControl::Keyboard;

std::map<sf::Keyboard::Key, std::string> ContextManager::_validKeys = {
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
std::map<int, std::string> ContextManager::_validPlatformCounts{
	{ 3, "3" },
	{ 4, "4" },
	{ 5, "5" },
	{ 6, "6" },
	{ 7, "7" },
	{ 8, "8" }
};
std::map<PlatformControl, std::string> _validPlatformControls{
	{ PlatformControl::Keyboard, "Keyboard" },
	{ PlatformControl::Mouse, "Mouse" }
};


bool ContextManager::setJumpKey(sf::Event::KeyEvent keyEvent) {
	if (_validKeys.find(keyEvent.code) != _validKeys.end()) {
		_jumpKey = keyEvent;
		return true;
	}
	return false;
}
void ContextManager::setPlatformCount(const std::string& number) { _platformCount = std::stoi(number); }
void ContextManager::setPlatformControl(const std::string& control) {
	if (control == "Keyboard") {
		_platformControl = PlatformControl::Keyboard;
	}
	else if (control == "Mouse") {
		_platformControl = PlatformControl::Mouse;
	}
}

std::pair<sf::Keyboard::Key, std::string> ContextManager::getJumpKey() { return *_validKeys.find(_jumpKey.code); }
std::pair<int, std::string> ContextManager::getPlatformCount() { return *_validPlatformCounts.find(_platformCount); }
std::pair<PlatformControl, std::string> ContextManager::getPlatformControl() { return /**_validPlatformControls.find(_platformControl);*/{ _platformControl, "Keyboard" }; }
