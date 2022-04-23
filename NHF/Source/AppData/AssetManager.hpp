#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AppData;


class AssetManager {
private:
	friend AppData;
	AssetManager() = default;


	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::SoundBuffer> _soundBuffers;
	std::map<std::string, sf::Sound> _sounds;
	std::map<std::string, sf::Texture> _textures;

	void loadFont(const std::string& name, const std::string& fileName);
	void loadSound(const std::string& name, const std::string& fileName);
	void loadTexture(const std::string& name, const std::string& fileName);

public:
	void init();

	const sf::Font& getFont(const std::string& name);
	sf::Sound& getSound(const std::string& name);
	const sf::Texture& getTexture(const std::string& name);
};

