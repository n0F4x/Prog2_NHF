#pragma once

#include "AssetManager.hpp"
#include "Engine.hpp"
#include "StageManager.hpp"
#include "WindowManager.hpp"


struct AppData {
	AssetManager assets;
	//InputManager inputs;
	Engine math;
	StageManager stages;
	WindowManager window;

	AppData();
};