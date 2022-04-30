#include "PlatformContainer.hpp"

#include "../../Window.hpp"


void PlatformContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto platform = _platforms.rbegin(); platform != _platforms.rend(); platform++) {
		target.draw(*platform);
	}
}

PlatformContainer::PlatformContainer(const PreCalculator& preCalc) : _preCalc{ preCalc } {
	Platform::setOrigin(Window::getSize() / 2.f);
	Platform::setScale(_scaleSpeed);
}

bool PlatformContainer::isInside(const sf::Vector2f& point) const {
	for (auto& platform : _platforms) {
		if (platform.isInside(point)) {
			return true;
		}
	}
	return false;
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
		_platforms.emplace_front(_preCalc);
		_platforms.front().rotate((rand() % (360 / static_cast<int>(Platform::width * 180.f / math::PI))) * Platform::width + _rotation);
		_counter = 0;
	}
}

void PlatformContainer::init() {
	_platforms.clear();
	_platforms.emplace_front(_preCalc);
	_counter = 0;
	_rotation = 0_deg;
}
