#include "MenuItem.hpp"


void MenuItem::update() {
	for (auto it : _transitions) {
		it->update();
	}
}

void MenuItem::init() {
	for (auto it : _transitions) {
		it->init();
	}
	_isPaused = false;
}

void MenuItem::pause() {
	for (auto it : _transitions) {
		it->pause();
	}
	_isPaused = true;
}

void MenuItem::resume() {
	for (auto it : _transitions) {
		it->resume();
	}
	_isPaused = false;
}
