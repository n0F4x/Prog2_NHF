#pragma once

#include "AppData/AssetManager.hpp"
#include "AppData/ContextManager.hpp"
#include "AppData/ContextRepr.hpp"

class App;


class AppData {
private:
	friend App;
	AppData() = default;

	static AssetManager _assets;
	static ContextManager _contexts;

public:
	static const sf::Font& getFont(const std::string& name) { return _assets.getFont(name); }
	static Context* findContext(const std::string_view& name) { return _contexts.find(name); }

	void loadFromFiles() const { 
		_assets.loadFromFiles();
		_contexts.loadFromFile();
	}
	void save() const {
		_contexts.save();
	}
};
