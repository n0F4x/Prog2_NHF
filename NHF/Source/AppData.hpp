#pragma once

#include "AppData/AssetManager.hpp"
#include "AppData/InputManager.hpp"


class AppData {
public:
	static AssetManager assets;
	static InputManager inputs;

	void init() {
		assets.init();
		inputs.init();
	}
};