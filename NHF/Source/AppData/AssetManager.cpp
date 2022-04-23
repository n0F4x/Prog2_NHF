#include "AssetManager.hpp"


void AssetManager::init() {
	loadFont("The Wireframe", "./Assets/the_wireframe_demo.otf");
	loadFont("Dameron", "./Assets/dameron.ttf");

	loadSound("ButtonHover", "./Assets/ButtonHover.wav");
	loadSound("ButtonClick", "./Assets/ButtonClick.wav");
	loadSound("ButtonRelease", "./Assets/ButtonRelease.wav");
}


void AssetManager::loadFont(const std::string& name, const std::string& fileName) {
	if (!_fonts.contains(name)) {
		if (sf::Font tmp; tmp.loadFromFile(fileName)) {
			_fonts[name] = tmp;
		}
	}
}

void AssetManager::loadTexture(const std::string& name, const std::string& fileName) {
	if (!_textures.contains(name)) {
		if (sf::Texture tmp; tmp.loadFromFile(fileName)) {
			_textures[name] = tmp;
		}
	}
}

void AssetManager::loadSound(const std::string& name, const std::string& fileName) {
	if (!_soundBuffers.contains(name)) {
		if (sf::SoundBuffer tmp; tmp.loadFromFile(fileName)) {
			_soundBuffers[name] = tmp;

			sf::Sound sound;
			sound.setBuffer(_soundBuffers[name]);
			_sounds[name] = sound;
		}
	}
}


const sf::Font& AssetManager::getFont(const std::string& name) {
	if (auto it = _fonts.find(name); it != _fonts.end())
		return it->second;
	return _fonts.begin()->second;
}

sf::Sound& AssetManager::getSound(const std::string& name) {
	if (auto it = _sounds.find(name); it != _sounds.end())
		return it->second;
	return _sounds.begin()->second;
}

const sf::Texture& AssetManager::getTexture(const std::string& name) {
	if (auto it = _textures.find(name); it != _textures.end())
		return it->second;
	return _textures.begin()->second;
}