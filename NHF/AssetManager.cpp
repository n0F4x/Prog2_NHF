#include "AssetManager.hpp"


AssetManager::AssetManager() {
	loadFont("Air Millhouse", "./Assets/airmill_o.ttf");
}

void AssetManager::loadTexture(std::string name, std::string fileName) {
	if (_textures.find(name) == _textures.end()) {
		sf::Texture tex;
		if (tex.loadFromFile(fileName)) {
			_textures[name] = tex;
		}
	}
}

sf::Texture& AssetManager::getTexture(std::string name) {
	return _textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string fileName) {
	if (_fonts.find(name) == _fonts.end()) {
		sf::Font font;
		if (font.loadFromFile(fileName)) {
			_fonts[name] = font;
		}
	}
}

sf::Font& AssetManager::getFont(std::string name) {
	return _fonts.at(name);
}