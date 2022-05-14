#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/**
 * @brief	Class for managing assets of the application
*/
class AssetManager {
private:
	std::map<const std::string, const sf::Font, std::less<>> _fonts;
	/**
	 * @brief	Tries adding font from file to AssetManager.
	 * @param name	Name of the font for future reference
	 * @param fileName	Path to the font asset file
	*/
	void loadFont(const std::string& name, const std::string& fileName);

	std::map<const std::string, const sf::Texture, std::less<>> _textures;
	/**
	 * @brief	Tries adding texture from file to AssetManager.
	 * @param name	Name of the texture for future reference
	 * @param fileName	Path to the texture asset file
	*/
	void loadTexture(const std::string& name, const std::string& fileName);

public:
	/**
	 * @brief	Getter for fonts. Returns reference to first font stored inside the class if one with the given name doesn't exist.
	 * @param name	Name of the font
	 * @return	Reference to font
	*/
	const sf::Font& getFont(const std::string_view& name);
	/**
	 * @brief	Getter for textures. Returns reference to first texture stored inside the class if one with the given name doesn't exist.
	 * @param name	Name of the texture
	 * @return	Reference to texture
	*/
	const sf::Texture& getTexture(const std::string_view& name);

	/**
	 * @brief	Reads and stores assets from the corresponding files
	*/
	void loadFromFiles();
};

