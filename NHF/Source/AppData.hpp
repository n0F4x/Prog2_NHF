#pragma once

#include "AppData/AssetManager.hpp"
#include "AppData/ContextManager.hpp"

class App;


class AppData {
private:
	friend App;
	AppData() = default;

public:
	static AssetManager assets;
	static ContextManager context;
};
