#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AppData;


class AssetManager {
private:
	friend AppData;
	AssetManager() = default;

	std::map<std::string, sf::Font, std::less<>> _fonts;
	void loadFont(const std::string& name, const std::string& fileName);

public:
	const sf::Font& getFont(const std::string& name);

	void loadFromFiles();
};

