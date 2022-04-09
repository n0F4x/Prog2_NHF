#include "Screen.hpp"
#include "Math.hpp"


void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_screen, states);
}

Screen::Screen(const PreCalculator& preCalc) :
	_preCalc{ preCalc },
	_screen{ sf::Points, static_cast<size_t>(_preCalc.getWindow().x) * static_cast<size_t>(_preCalc.getWindow().y) }
{
	for (size_t x = 0; x < _preCalc.getWindow().x; x++) {
		for (size_t y = 0; y < _preCalc.getWindow().y; y++) {
			size_t index = x * static_cast<size_t>(_preCalc.getWindow().y) + y;
			_screen[index].position = { static_cast<float>(x), static_cast<float>(y) };
		}
	}
}

void Screen::update(const PlatformContainer& platforms) {
	_screen.clear();
	auto platform = platforms.getList().begin();
	for (auto it = _preCalc.getCircularVectorMap().begin(); it != _preCalc.getCircularVectorMap().end() && platform != platforms.getList().end(); ++it) {
		for (size_t index : it->second) {
			if (math::isBetween(_preCalc.getPolarVector(index).angle, platform->getRotation(), platform->getRotation() + platform->getWidth())) {
				_screen.append(sf::Vertex{ {static_cast<float>(index) / _preCalc.getWindow().y, static_cast<float>(index % _preCalc.getWindow().y), }, _preCalc.getColor(index) });
			}
		}
		
		if (it->first >= platform->getOuterRadius()) {
			++platform;
		}
	}
}

void Screen::init() {
	for (size_t i = 0; i < _screen.getVertexCount(); i++)
		_screen[i].color = sf::Color::Transparent;
}
