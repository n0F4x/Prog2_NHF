#pragma once

#include "AssetManager.hpp"
#include "Engine.hpp"
#include "MenuManager.hpp"
#include "Window.hpp"


struct AppData {
	AssetManager assets;
	Engine engine;
	MenuManager menus;
	Window window{ menus };

	void init() {
		assets.init();
		engine.init();
		window.init();
		menus.init(*this);
	}
};