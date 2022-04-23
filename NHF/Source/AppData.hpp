#pragma once

#include "AppData/AssetManager.hpp"
#include "AppData/ContextManager.hpp"


class AppData {
public:
	// Data
	static AssetManager assets;
	static ContextManager context;

	// Functions
	AppData() = delete;

	static void init() {
		assets.init();
		context.init();
	}
};
