#pragma once

#include <map>
#include <string>
#include <vector>
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

	// Contexts
	sf::Event::KeyEvent _jumpKey = { sf::Keyboard::Space };
	int _platformCount = 3;
	PlatformControl _platformControl = PlatformControl::Keyboard;
	sf::Event::KeyEvent _switchKey1 = { sf::Keyboard::Left};
	sf::Event::KeyEvent _switchKey2 = { sf::Keyboard::Right };

public:
	void init() const { /*TODO*/ }
	void save() const { /*TODO*/ }

	bool setJumpKey(const sf::Event::KeyEvent& keyEvent);
	bool setPlatformCount(int amount);
	bool setPlatformControl(const PlatformControl& control);
	bool setSwitchKey1(const sf::Event::KeyEvent& keyEvent);
	bool setSwitchKey2(const sf::Event::KeyEvent& keyEvent);

	std::pair<const sf::Keyboard::Key, const std::string> getJumpKey() const;
	std::pair<const int, const std::string> getPlatformCount() const;
	std::pair<const PlatformControl, const std::string> getPlatformControl() const;
	std::pair<const sf::Keyboard::Key, const std::string> getSwitchKey1() const;
	std::pair<const sf::Keyboard::Key, const std::string> getSwitchKey2() const;

private:
	const std::map<const sf::Keyboard::Key, const std::string> _validKeys{
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
	const std::vector<int> _validPlatformCounts{ 3, 4, 5, 6, 7, 8 };
};
