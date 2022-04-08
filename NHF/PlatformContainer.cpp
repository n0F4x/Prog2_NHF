#include "PlatformContainer.hpp"


PlatformContainer::PlatformContainer(const sf::Window& window) {
	Platform::setOrigin(sf::Vector2f{ window.getSize() / 2u });
	Platform::setScale(_scaleSpeed);
}

const std::list<Platform>& PlatformContainer::getList() const {
	return _platforms;
}

void PlatformContainer::rotate(float angle) {
	for (auto& platform : _platforms)
		platform.rotate(angle);
	_rotation += angle;
}

void PlatformContainer::update() {
	_counter++;
	for (auto& platform : _platforms)
		platform.update();

	while (!_platforms.empty() && _platforms.back().isDead()) {
		_platforms.pop_back();
	}

	if (_counter >= _scaleSpeed) {
		_platforms.emplace_front();
		_platforms.front().rotate((rand() % 12) * 30_deg + _rotation);
		_counter = 0;
	}
}

void PlatformContainer::init() {
	_platforms.clear();
	_platforms.emplace_front();
	_counter = 0;
	_rotation = 0_deg;
}
