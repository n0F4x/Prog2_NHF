#pragma once

#include "AssetManager.hpp"
#include "Engine.hpp"
#include "MenuManager.hpp"
#include "WindowManager.hpp"


struct AppData {
	AssetManager assets;
	Engine engine;
	MenuManager menus;
	WindowManager window;

	AppData();
};