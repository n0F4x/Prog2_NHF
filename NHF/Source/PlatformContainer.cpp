#include "PlatformContainer.hpp"

#include "Window.hpp"


void PlatformContainer::draw(sf::RenderTarget& target, const sf::RenderStates& states) const { /*Removed visuals*/ }

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
		_platforms.front().rotate(static_cast<float>(std::uniform_int_distribution<int>( 0, 360 / static_cast<int>(Platform::width * 180.f / math::PI) )(_randomEngine)) * Platform::width + _rotation);
		_counter = 0;
	}
}

void PlatformContainer::init() {
	_platforms.clear();
	_platforms.emplace_front(_preCalc);
	_counter = 0;
	_rotation = 0_deg;
}
