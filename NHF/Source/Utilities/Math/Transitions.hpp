#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "BezierEasing.hpp"


class Transitionable;


namespace Transitions {
	class Transition {
	protected:
		Transitionable* _object = nullptr;

		int _time = 0;	// in milliseconds
		sf::Vector2f _distance = { 0, 0 };

		bool _isActive = false;

		// During transition variables
		sf::Clock _clock;
		int _currentTime = 0;
		sf::Vector2f _currentDistance = { 0.f, 0.f };

	public:
		Transition(Transitionable* object) : _object{ object } {}

		virtual void start(const sf::Vector2f& distance, int time) {
			if (!_isActive) {
				_distance = distance;
				_time = time;
				_clock.restart();
				_isActive = true;
			}
		}
		virtual void update() = 0;
		virtual void init() { _isActive = false;  _currentTime = 0; _currentDistance = { 0.f, 0.f }; }
	};

	class EaseInOut : public Transition {	// Quadratic
	private:
		float _accX = 0;	// max X acceleration during rotation
		float _accY = 0;	// max Y acceleration during rotation

		float getAccX() { return _distance.x / static_cast<float>(_time / 2 * _time / 2); }
		float getAccY() { return _distance.y / static_cast<float>(_time / 2 * _time / 2); }

	public:
		EaseInOut(Transitionable* object) : Transition{ object } {}

		void start(const sf::Vector2f& distance, int time) override {
			if (!_isActive) {
				_distance = distance;
				_time = time;
				_accX = getAccX();
				_accY = getAccY();
				_clock.restart();
				_isActive = true;
			}
		}
		void update() override;
	};

	class Ease : public Transition {	// Cubic Bezier
	private:
		BezierEasing _bezier{ {0.25f, 0.1f}, {0.25f, 0.1f} };
		float _lastProgress = 0.f;

	public:
		Ease(Transitionable* object) : Transition{ object } {}

		void start(const sf::Vector2f& distance, int time) override {
			if (!_isActive) {
				_lastProgress = 0.f;
				_distance = distance;
				_time = time;
				_clock.restart();
				_isActive = true;
			}
		}
		void update() override;
	};
}