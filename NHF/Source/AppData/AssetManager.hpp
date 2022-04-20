#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AppData;


class AssetManager {
private:
	friend AppData;
	AssetManager() = default;


	static std::map<std::string, sf::Font> _fonts;
	static std::map<std::string, sf::SoundBuffer> _soundBuffers;
	static std::map<std::string, sf::Sound> _sounds;
	static std::map<std::string, sf::Texture> _textures;

	static void loadFont(std::string name, std::string fileName);
	static void loadSound(std::string name, std::string fileName);
	static void loadTexture(std::string name, std::string fileName);

public:
	static void init();

	static const sf::Font& getFont(std::string name);
	static sf::Sound& getSound(std::string name);
	static const sf::Texture& getTexture(std::string name);
};

