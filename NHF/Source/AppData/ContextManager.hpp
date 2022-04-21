#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class AppData;


enum class PlatformControl {
	Keyboard,
	Mouse
};


class ContextManager {
private:
	friend AppData;
	ContextManager() = default;


	static std::map<sf::Keyboard::Key, std::string> _validKeys;				//	code / name
	static std::map<int, std::string> _validPlatformCounts;					//	code / name
	static std::map<PlatformControl, std::string> _validPlatformControls;	//	code / name

	// Contexts
	static sf::Event::KeyEvent _jumpKey;
	static int _platformCount;
	static PlatformControl _platformControl;
	static sf::Event::KeyEvent _switchKey1;
	static sf::Event::KeyEvent _switchKey2;

public:
	static void init() {}
	static void save() {}

	static bool setJumpKey(const sf::Event::KeyEvent& keyEvent);
	static void setPlatformCount(const std::string& number);
	static void setPlatformControl(const std::string& control);
	static bool setSwitchKey1(const sf::Event::KeyEvent& keyEvent);
	static bool setSwitchKey2(const sf::Event::KeyEvent& keyEvent);

	static std::pair<sf::Keyboard::Key, std::string> getJumpKey();
	static std::pair<int, std::string> getPlatformCount();
	static std::pair<PlatformControl, std::string> getPlatformControl();
	std::pair<sf::Keyboard::Key, std::string> getSwitchKey1();
	std::pair<sf::Keyboard::Key, std::string> getSwitchKey2();
};
