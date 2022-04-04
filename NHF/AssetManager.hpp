#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class AssetManager {
private:
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::SoundBuffer> _soundBuffers;
	std::map<std::string, sf::Sound> _sounds;
	std::map<std::string, sf::Texture> _textures;

	void loadFont(std::string name, std::string fileName);
	void loadSound(std::string name, std::string fileName);
	void loadTexture(std::string name, std::string fileName);

public:
	AssetManager();

	const sf::Font& getFont(std::string name) const;
	sf::Sound& getSound(std::string name);
	const sf::Texture& getTexture(std::string name) const;
};

