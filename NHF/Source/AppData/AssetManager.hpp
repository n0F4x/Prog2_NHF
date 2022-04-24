#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AppData;


class AssetManager {
private:
	std::map<std::string, sf::Font, std::less<>> _fonts;

	void loadFont(const std::string& name, const std::string& fileName);

	friend AppData;
	AssetManager();

public:
	const sf::Font& getFont(const std::string& name);
};

