#include "PlatformContainer.hpp"

#include "../../Core/Window.hpp"
#include "../../Utilities/Math.hpp"


int PlatformContainer::generateRandom(int from, int to) {
	return _random ? std::uniform_int_distribution{ from, to }(_randomEngine) : 0;
}

void PlatformContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto platform = _platforms.rbegin(); platform != _platforms.rend(); platform++) {
		target.draw(*platform);
	}
}


PlatformContainer::PlatformContainer(const PreCalculator& preCalc) : _preCalc{ preCalc } {
	Platform::setOrigin(Window::getSize() / 2.f);

	init(8u, 6u);
}


bool PlatformContainer::isInside(const PolarVector& point) const {
	return std::ranges::any_of(_platforms, [point](auto& platform) -> bool { return platform.isInside(point); });
}

bool PlatformContainer::AI_help(PolarVector playerFeet, int& switchingState) {
	for (auto it = _platforms.begin() + 6u; it != _platforms.end(); it++) {
		if (it->isInside(playerFeet)) {
			float offset = 50.f;
			playerFeet.radius -= offset;
			if (it->isInside(playerFeet) || (it - 1)->isInside(playerFeet)) {
				return false;
			}

			it -= 7;
			if (it->isInside(playerFeet)) {
				return true;
			}
			it->rotate(-90_deg + _platformWidth / 2.f + 1_deg);
			if (float rotation = it->getRotation(); rotation <= 180_deg) {
				switchingState = -static_cast<int>(rotation / _platformWidth);
			}
			else {
				switchingState = static_cast<int>((360_deg - rotation) / _platformWidth) + 1;
			}
			it->rotate(90_deg - _platformWidth / 2.f - 1_deg);
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
		int random_number = generateRandom(0, 360 / static_cast<int>(math::convertToDeg(_platformWidth)));
		float initialRotation = static_cast<float>(random_number) * getPlatformWidth() + _rotation + 90_deg - getPlatformWidth() / 2.f;
		_platforms.emplace_front(_preCalc, initialRotation, _platformWidth, _scaleSpeed);
		_counter = 0;
	}
}

void PlatformContainer::init(unsigned laneCount, unsigned speed) {
	_platformWidth = 360_deg / static_cast<float>(laneCount);
	_scaleSpeed = speed;

	_platforms.clear();
	_platforms.emplace_front(_preCalc, 90_deg - _platformWidth / 2.f, _platformWidth, _scaleSpeed);
	_counter = 0;
	_rotation = 0_deg;

	float inner = _platforms.front().getInnerRadius();
	float outer = _platforms.front().getOuterRadius();

	float maxRadius = sqrt(math::square(Window::getSize().x / 2.f) + math::square(Window::getSize().y / 2.f));
	auto platformCount = static_cast<unsigned>((maxRadius - inner) / outer);

	_random = false;
	for (unsigned i = 0; i < _scaleSpeed * platformCount; i++) {
		update();
	}
	_random = true;
}
