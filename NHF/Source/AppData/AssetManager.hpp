#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AppData;


class AssetManager {
private:
	std::map<std::string, sf::Font, std::less<>> _fonts;
	std::map<std::string, sf::SoundBuffer, std::less<>> _soundBuffers;
	std::map<std::string, sf::Sound, std::less<>> _sounds;
	std::map<std::string, sf::Texture, std::less<>> _textures;

	void loadFont(const std::string& name, const std::string& fileName);
	void loadSound(const std::string& name, const std::string& fileName);
	void loadTexture(const std::string& name, const std::string& fileName);

	friend AppData;
	AssetManager();

public:
	const sf::Font& getFont(const std::string& name);
	sf::Sound& getSound(const std::string& name);
	const sf::Texture& getTexture(const std::string& name);
};

