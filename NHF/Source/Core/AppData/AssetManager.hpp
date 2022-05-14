#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class AssetManager {
private:
	std::map<const std::string, const sf::Font, std::less<>> _fonts;
	void loadFont(const std::string& name, const std::string& fileName);

	std::map<const std::string, const sf::Texture, std::less<>> _textures;
	void loadTexture(const std::string& name, const std::string& fileName);

public:
	const sf::Font& getFont(const std::string_view& name);
	const sf::Texture& getTexture(const std::string_view& name);

	void loadFromFiles();
};

