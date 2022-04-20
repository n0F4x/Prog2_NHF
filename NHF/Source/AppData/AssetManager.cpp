#include "AssetManager.hpp"


std::map<std::string, sf::Font> AssetManager::_fonts;
std::map<std::string, sf::SoundBuffer> AssetManager::_soundBuffers;
std::map<std::string, sf::Sound> AssetManager::_sounds;
std::map<std::string, sf::Texture> AssetManager::_textures;


void AssetManager::init() {
	loadFont("The Wireframe", "./Assets/the_wireframe_demo.otf");
	loadFont("Dameron", "./Assets/dameron.ttf");

	loadSound("ButtonHover", "./Assets/ButtonHover.wav");
	loadSound("ButtonClick", "./Assets/ButtonClick.wav");
	loadSound("ButtonRelease", "./Assets/ButtonRelease.wav");
}


void AssetManager::loadFont(std::string name, std::string fileName) {
	if (_fonts.find(name) == _fonts.end()) {
		sf::Font tmp;
		if (tmp.loadFromFile(fileName)) {
			_fonts[name] = tmp;
		}
	}
}

void AssetManager::loadTexture(std::string name, std::string fileName) {
	if (_textures.find(name) == _textures.end()) {
		sf::Texture tmp;
		if (tmp.loadFromFile(fileName)) {
			_textures[name] = tmp;
		}
	}
}

void AssetManager::loadSound(std::string name, std::string fileName) {
	if (_soundBuffers.find(name) == _soundBuffers.end()) {
		sf::SoundBuffer tmp;
		if (tmp.loadFromFile(fileName)) {
			_soundBuffers[name] = tmp;

			sf::Sound sound;
			sound.setBuffer(_soundBuffers[name]);
			_sounds[name] = sound;
		}
	}
}


const sf::Font& AssetManager::getFont(std::string name) {
	if (_fonts.find(name) != _fonts.end())
		return _fonts.at(name);
	return _fonts.begin()->second;
}

sf::Sound& AssetManager::getSound(std::string name) {
	if (_sounds.find(name) != _sounds.end())
		return _sounds.at(name);
	return _sounds.begin()->second;
}

const sf::Texture& AssetManager::getTexture(std::string name) {
	if (_textures.find(name) != _textures.end())
		return _textures.at(name);
	return _textures.begin()->second;
}