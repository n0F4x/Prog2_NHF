#pragma once

#include "AppData/AssetManager.hpp"
#include "AppData/ContextManager.hpp"


class AppData {
public:
	static AssetManager assets;
	static ContextManager context;

	AppData() = delete;
	static void init() {
		assets.init();
		context.init();
	}
};