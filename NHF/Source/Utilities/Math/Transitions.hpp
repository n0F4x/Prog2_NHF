#pragma once

#include <SFML/System.hpp>


namespace Direction {
	static const int POSITIVE = 1;
	static const int NEGATIVE = -1;
};

class Transitionable;


namespace Transitions {
	class Transition {
	protected:
		Transitionable* _object = nullptr;

		int _time = 0;	// in milliseconds
		float _length = 0;

		bool _isActive = false;

		// During transition variables
		int _direction = Direction::POSITIVE;
		sf::Clock _clock;
		int _currentTime = 0;
		float _currentLength = 0.f;

	public:
		Transition(Transitionable* object) : _object{ object } {}
		Transition(Transitionable* object, int time, float length) : _object{ object }, _time{ time }, _length{ length } {
			if (_length < 0) {
				_direction = Direction::NEGATIVE;
				_length *= -1;
			}
		}

		virtual void setObject(Transitionable* object) { _object = object; }
		virtual void setTime(int time) { _time = time; }
		virtual void setLength(float length) {
			_length = length;
			if (_length < 0) {
				_direction = Direction::NEGATIVE;
				_length *= -1;
			}
		}
		virtual void setDirection(int direction) { _direction = direction; };

		virtual void start() {
			if (!_isActive) {
				_clock.restart();
				_isActive = true;
			}
		}virtual void start(int direction) {
			if (!_isActive) {
				_direction = direction;
				_clock.restart();
				_isActive = true;
			}
		}
		virtual void update() = 0;
		virtual void init() { _isActive = false; _direction = Direction::POSITIVE; _currentTime = 0; _currentLength = 0.f; }
	};

	class EaseInOut : public Transition {	// Quadratic
	private:
		float _acceleration = _length / static_cast<float>(_time / 2 * _time / 2);	// max acceleration during rotation

	public:
		EaseInOut(Transitionable* object) : Transition{ object } {}
		EaseInOut(Transitionable* object, int time, float length) : Transition{ object, time, length } {}

		virtual void setTime(int time) override { Transition::setTime(time); _acceleration = _length / static_cast<float>(_time / 2 * _time / 2); }
		virtual void setLength(float length) override { Transition::setLength(length); _acceleration = _length / static_cast<float>(_time / 2 * _time / 2); }

		void update() override;
	};
}
