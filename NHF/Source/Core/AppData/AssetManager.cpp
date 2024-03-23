#include "AssetManager.hpp"


void AssetManager::loadFont(const std::string& name, const std::string& fileName) {
	if (!_fonts.contains(name)) {
		if (sf::Font tmp; tmp.loadFromFile(fileName)) {
			_fonts.try_emplace(name, tmp);
		}
	}
}

void AssetManager::loadTexture(const std::string& name, const std::string& fileName) {
	if (!_textures.contains(name)) {
		if (sf::Texture tmp; tmp.loadFromFile(fileName)) {
			_textures.try_emplace(name, tmp);
		}
	}
}


const sf::Font& AssetManager::getFont(const std::string_view& name) {
	if (auto it = _fonts.find(name); it != _fonts.end())
		return it->second;
	return _fonts.begin()->second;
}

const sf::Texture& AssetManager::getTexture(const std::string_view& name) {
	if (auto it = _textures.find(name); it != _textures.end())
		return it->second;
	return _textures.begin()->second;
}


void AssetManager::loadFromFiles() {
	loadFont("The Wireframe", "./Assets/the_wireframe_demo.otf");
	loadFont("Dameron", "./Assets/dameron.ttf");

	loadTexture("Motor", "./Assets/Motor.png");
}

void AssetManager::release() {
    _fonts.clear();
    _textures.clear();
}
