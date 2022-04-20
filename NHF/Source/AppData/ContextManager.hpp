#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>


enum class PlatformControl {
	Keyboard,
	Mouse
};


class ContextManager {
private:
	static std::map<sf::Keyboard::Key, std::string> _validKeys;				//	code / name
	static std::map<int, std::string> _validPlatformCounts;					//	code / name
	static std::map<PlatformControl, std::string> _validPlatformControls;	//	code / name

	// Contexts
	static sf::Event::KeyEvent _jumpKey;
	static int _platformCount;
	static PlatformControl _platformControl;

public:
	static void init() {}
	static void save() {}

	static bool setJumpKey(sf::Event::KeyEvent keyEvent);
	static void setPlatformCount(const std::string& number);
	static void setPlatformControl(const std::string& control);

	static std::pair<sf::Keyboard::Key, std::string> getJumpKey();
	static std::pair<int, std::string> getPlatformCount();
	static std::pair<PlatformControl, std::string> getPlatformControl();
};
