#include "ContextManager.hpp"

#include <algorithm>


// Setters
bool ContextManager::setJumpKey(const sf::Event::KeyEvent& keyEvent) {
	if (_validKeys.contains(keyEvent.code)) {
		_jumpKey = keyEvent;
		return true;
	}
	return false;
}

bool ContextManager::setPlatformCount(int amount) {
	if (std::ranges::any_of(_validPlatformCounts, [amount](auto const& elem) { return elem == amount; })) {
		_platformCount = amount;
		return false;
	}
	return false;
}

bool ContextManager::setPlatformControl(const PlatformControl& control) {
	switch (control) {
	case PlatformControl::Keyboard:
	case PlatformControl::Mouse:
		_platformControl = control;
		return true;
	default:
		return false;
	}
}

bool ContextManager::setSwitchKey1(const sf::Event::KeyEvent& keyEvent) {
	if (_validKeys.contains(keyEvent.code)) {
		_switchKey1 = keyEvent;
		return true;
	}
	return false;
}

bool ContextManager::setSwitchKey2(const sf::Event::KeyEvent& keyEvent) {
	if (_validKeys.contains(keyEvent.code)) {
		_switchKey2 = keyEvent;
		return true;
	}
	return false;
}


// Getters
std::pair<const sf::Event::KeyEvent&, const std::string&> ContextManager::getJumpKey() const {
	return { _jumpKey, _validKeys.at(_jumpKey.code) };
}

std::pair<const int, const std::string&> ContextManager::getPlatformCount() const {
	return { _platformCount, std::to_string(_platformCount) };
}

std::pair<const PlatformControl&, const std::string&> ContextManager::getPlatformControl() const {
	std::string name;
	switch (_platformControl) {
	case PlatformControl::Keyboard:
		name = "Keyboard";
		break;
	case PlatformControl::Mouse:
		name = "Mouse";
		break;
	default:
		break;
	}
	return { _platformControl, name };
}

std::pair<const sf::Event::KeyEvent&, const std::string&> ContextManager::getSwitchKey1() const {
	return { _switchKey1, _validKeys.at(_switchKey1.code) };
}

std::pair<const sf::Event::KeyEvent&, const std::string&> ContextManager::getSwitchKey2() const {
	return { _switchKey2, _validKeys.at(_switchKey2.code) };
}


bool operator==(const sf::Event::KeyEvent& lhs, const sf::Event::KeyEvent& rhs) {
	return
		lhs.alt == rhs.alt &&
		lhs.code == rhs.code &&
		lhs.control == rhs.control &&
		lhs.shift == rhs.shift &&
		lhs.system == rhs.system;
}

