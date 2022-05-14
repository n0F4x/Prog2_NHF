#pragma once

#include "AppData/AssetManager.hpp"
#include "AppData/ContextManager.hpp"
#include "AppData/ContextRepr.hpp"


/**
 * @brief	Class for managing global application information
*/
class AppData {
private:
	static AssetManager _assets;
	static ContextManager _contexts;

public:
	/**
	 * @brief	Getter for font assets
	 * @param name	Name of the font
	 * @return	Reference to font
	*/
	static const sf::Font& getFont(const std::string_view& name) { return _assets.getFont(name); }
	/**
	 * @brief	Getter for texture assets
	 * @param name	Name of the texture
	 * @return	Reference to texture
	*/
	static const sf::Texture& getTexture(const std::string_view& name) { return _assets.getTexture(name); }
	/**
	 * @brief	Searches for context by name
	 * @param name	Name of the desired context
	 * @return	Pointer to the found context. Nullptr if not found
	*/
	static Context* findContext(const std::string_view& name) { return _contexts.find(name); }

	/**
	 * @brief	Loads assets from files
	*/
	void loadAssets() const { _assets.loadFromFiles(); }
	/**
	 * @brief	Loads contexts from file
	*/
	void loadContexts() const { _contexts.loadFromFile(); }
	/**
	 * @brief	Saves contexts to file
	*/
	void save() const { _contexts.save(); }
};
