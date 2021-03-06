#include "Transitions.hpp"


Transition::Transition(
	Transitionable* object,
	const std::function<sf::Vector2f(int elapsedTime)>& getProgression,
	const std::function<sf::Vector2f()>& correctDistance
) :
	_object{ object }, _getProgression{ getProgression }, _correctDistance{ correctDistance }
{
	if (_correctDistance == nullptr) {
		_correctDistance = [this]() -> sf::Vector2f { return _distance - _distanceTraveled; };
	}
}

void Transition::update() {
	if (_isActive && !_isPaused) {
		if (int elapsedTime = _clock.getElapsedTime().asMilliseconds() - _pausedTime; elapsedTime >= _time) {
			_object->transition(_correctDistance());
			init();
		}
		else {
			sf::Vector2f progression = _getProgression(elapsedTime);
			_elapsedTime = elapsedTime;
			_distanceTraveled += progression;
			_object->transition(progression);
		}
	}
}

namespace Transitions {
	EaseInOut::EaseInOut(Transitionable* object) :
		Transition{
			object,
			[this](int elapsedTime) -> sf::Vector2f {
				sf::Vector2f progression;
				if (elapsedTime <= getDurationTime() / 2) {
					progression = _acc / 2.f * static_cast<float>(math::square(elapsedTime)) - getDistanceTraveled();
				}
				else {
					progression =
						-_acc / 2.f * static_cast<float>(math::square(elapsedTime - getDurationTime() / 2))
						+ _velocity2 * static_cast<float>(elapsedTime - getDurationTime() / 2)
						- (getDistanceTraveled() - getDurationDistance() / 2.f);
				}
				return progression;
			}
	} {
		/* Comment for formatting purposes */
	}

	namespace Bezier {
		Ease::Ease(Transitionable* object) :
			Transition{
				object,
				[this](int elapsedTime) -> sf::Vector2f {
				return
					_bezier.GetEasingProgress(static_cast<float>(elapsedTime) / static_cast<float>(getDurationTime())) * getDurationDistance()
					- getDistanceTraveled();
				}
		} {}
	}

	Jump::Jump(Transitionable* object) :
		Transition{
			object,
			[this](int elapsedTime) -> sf::Vector2f {
				return _acc / 2.f * static_cast<float>(math::square(elapsedTime)) + _velocity * static_cast<float>(elapsedTime) - getDistanceTraveled();
			},
			[this]() { return -getDistanceTraveled(); }
	} {}
}
