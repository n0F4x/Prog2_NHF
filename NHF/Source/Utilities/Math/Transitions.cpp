#include "Transitions.hpp"

#include "Transitionable.hpp"


void Transition::update() {
	if (_isActive && !_isPaused) {
		if (int elapsedTime = _clock.getElapsedTime().asMilliseconds() - _pausedTime; elapsedTime >= _time) {
			_object->transition(_distance - _distanceTraveled);
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
		Transition{ object, [this](int elapsedTime) -> sf::Vector2f {
			sf::Vector2f progression;
			if (elapsedTime <= getDurationTime() / 2) {
				progression = {
					_accX / 2.f * math::square(elapsedTime) - _accX / 2.f * math::square(getElapsedTime()),
					_accY / 2.f * math::square(elapsedTime) - _accY / 2.f * math::square(getElapsedTime())
				};
			}
			else {
				progression = {
					_accX / 2.f * math::square(getDurationTime() - getElapsedTime()) - _accX / 2.f * math::square(getDurationTime() - elapsedTime),
					_accY / 2.f * math::square(getDurationTime() - getElapsedTime()) - _accY / 2.f * math::square(getDurationTime() - elapsedTime)
				};
			}
			return progression;
		}
	} {}

		namespace Bezier {
			Ease::Ease(Transitionable* object) :
				Transition{ object, [this](int elapsedTime) -> sf::Vector2f {
					float progressionF = _bezier.GetEasingProgress(static_cast<float>(elapsedTime) / static_cast<float>(getDurationTime())) - _lastProgress;
					sf::Vector2f progression = getDurationDistance() * progressionF;

					_lastProgress += progressionF;
					return progression;
				}
			} {}
		}

		Jump::Jump(Transitionable* object) :
			Transition{ object, [this](int elapsedTime) -> sf::Vector2f {
				float progressionF = _acc / 2.f * math::square(elapsedTime) + _velocity * static_cast<float>(elapsedTime) - _lastProgress;
				sf::Vector2f progression = sf::Vector2f{ _direction } *progressionF;

				_lastProgress += progressionF;
				return progression;
			}
		} {}
}
