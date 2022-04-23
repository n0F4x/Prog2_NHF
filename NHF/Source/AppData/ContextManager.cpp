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
	for (auto valid : _validPlatformCounts) {
		_platformCount = amount;
		return true;
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
std::pair<const sf::Keyboard::Key, const std::string> ContextManager::getJumpKey() const { 
	return *_validKeys.find(_jumpKey.code); 
}

std::pair<const int, const std::string> ContextManager::getPlatformCount() const { 
	return {_platformCount, std::to_string(_platformCount)}; 
}

std::pair<const PlatformControl, const std::string> ContextManager::getPlatformControl() const { 
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

std::pair<const sf::Keyboard::Key, const std::string> ContextManager::getSwitchKey1() const {
	return *_validKeys.find(_switchKey1.code); 
}

std::pair<const sf::Keyboard::Key, const std::string> ContextManager::getSwitchKey2() const { 
	return *_validKeys.find(_switchKey2.code); 
}
