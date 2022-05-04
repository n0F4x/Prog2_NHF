#include "AssetManager.hpp"


void AssetManager::loadFont(const std::string& name, const std::string& fileName) {
	if (!_fonts.contains(name)) {
		if (sf::Font tmp; tmp.loadFromFile(fileName)) {
			_fonts[name] = tmp;
		}
	}
}


const sf::Font& AssetManager::getFont(const std::string& name) {
	if (auto it = _fonts.find(name); it != _fonts.end())
		return it->second;
	return _fonts.begin()->second;
}


void AssetManager::loadFromFiles() {
	loadFont("The Wireframe", "./Assets/the_wireframe_demo.otf");
	loadFont("Dameron", "./Assets/dameron.ttf");
}
