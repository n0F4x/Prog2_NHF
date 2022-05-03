#include "PlatformContainer.hpp"

#include "../../Window.hpp"


int PlatformContainer::generateRandom(int from, int to) {
	return std::uniform_int_distribution{ from, to }(_randomEngine);
}

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
	return std::ranges::any_of(_platforms, [point](auto& platform) -> bool { return platform.isInside(point); });
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
		int random_number = generateRandom(0, 360 / static_cast<int>(math::convertToDeg(Platform::width)));
		float initialRotation = static_cast<float>(random_number) * Platform::width + _rotation + 90_deg - Platform::width / 2.f;
		_platforms.emplace_front(_preCalc, initialRotation);
		_counter = 0;
	}
}

void PlatformContainer::init() {
	_platforms.clear();
	_platforms.emplace_front(_preCalc);
	_counter = 0;
	_rotation = 0_deg;
}
