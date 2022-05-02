#pragma once

#include <functional>
#include "SFMLVector2.hpp"
#include "BezierEasing.hpp"
#include "Math.hpp"


class Transitionable;


class Transition {
private:
	Transitionable* _object = nullptr;
	std::function<sf::Vector2f(int elapsedTime)> _getProgression;

	int _time = 0;	// in milliseconds
	sf::Vector2f _distance = { 0, 0 };

	bool _isActive = false;

	// During transition variables
	int _elapsedTime = 0;
	sf::Vector2f _distanceTraveled = { 0.f, 0.f };

	// Paused
	bool _isPaused = false;
	int _pausedTime = 0;

protected:
	explicit Transition(Transitionable* object, const std::function<sf::Vector2f(int elapsedTime)>& getProgression) :
		_object{ object }, _getProgression{ getProgression } {}

	int getDurationTime() const { return _time; }
	const sf::Vector2f& getDurationDistance() const { return _distance; }
	int getElapsedTime() const { return _elapsedTime; }

public:
	bool isActive() const { return _isActive; }

	virtual void start(const sf::Vector2f& distance, int time) {
		if (!_isActive) {
			init();
			_distance = distance;
			_time = time;
			_isActive = true;
		}
	}
	void update();
	virtual void init() { _isActive = false; _elapsedTime = 0; _distanceTraveled = { 0.f, 0.f }; _isPaused = false; _pausedTime = 0; }
	virtual void pause() { _isPaused = true; }
	virtual void resume() { _isPaused = false; }

	virtual ~Transition() = default;
};

namespace Transitions {
	class EaseInOut : public Transition {	// Quadratic
	private:
		float _accX = 0;	// max X acceleration during rotation
		float _accY = 0;	// max Y acceleration during rotation

		float getAccX(float distanceX, int time) const { return distanceX / math::square(time / 2); }
		float getAccY(float distanceY, int time) const { return distanceY / math::square(time / 2); }

	public:
		explicit EaseInOut(Transitionable* object);

		void start(const sf::Vector2f& distance, int time) override {
			if (!isActive()) {
				_accX = getAccX(distance.x, time);
				_accY = getAccY(distance.y, time);
				Transition::start(distance, time);
			}
		}
	};

	namespace Bezier {
		class Ease : public Transition {	// Cubic Bezier
		private:
			BezierEasing _bezier{ { 0.25f, 0.1f }, { 0.25f, 1.f } };
			float _lastProgress = 0.f;

		public:
			explicit Ease(Transitionable* object);

			void start(const sf::Vector2f& distance, int time) override {
				if (!isActive()) {
					_lastProgress = 0.f;
					Transition::start(distance, time);
				}
			}
		};
	}

	class Jump : public Transition {
	private:
		float _acc = -9.81f / (1000.f * 1000.f);
		float _velocity = 0.f;
		float _lastProgress = 0.f;

	public:
		explicit Jump(Transitionable* object);

		void start(const sf::Vector2f& distance, int time) override {
			if (!isActive()) {
				_lastProgress = 0.f;
				_velocity = -1.f * (_acc / 2.f * math::square(time)) / static_cast<float>(time);
				Transition::start({ 0.f, 0.f }, time);
			}
		}
	};
}
