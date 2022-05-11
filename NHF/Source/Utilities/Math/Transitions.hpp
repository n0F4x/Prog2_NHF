#pragma once

#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Transitionable.hpp"
#include "BezierEasing.hpp"
#include "../Math.hpp"


class Transition {
private:
	Transitionable* _object = nullptr;
	const std::function<sf::Vector2f(int elapsedTime)> _getProgression;
	std::function<sf::Vector2f()> _correctDistance;

	int _time = 0;	// in milliseconds
	sf::Vector2f _distance = { 0, 0 };

	bool _isActive = false;

	// During transition variables
	sf::Clock _clock;
	int _elapsedTime = 0;
	sf::Vector2f _distanceTraveled = { 0.f, 0.f };

	// Paused
	bool _isPaused = false;
	int _pausedTime = 0;
	sf::Clock _pausedClock;

protected:
	explicit Transition(
		Transitionable* object,
		const std::function<sf::Vector2f(int elapsedTime)>& getProgression,
		const std::function<sf::Vector2f()>& correctDistance = nullptr
	);

	int getDurationTime() const { return _time; }
	const sf::Vector2f& getDurationDistance() const { return _distance; }
	int getElapsedTime() const { return _elapsedTime; }
	const sf::Vector2f& getDistanceTraveled() const { return _distanceTraveled; }

public:
	bool isActive() const { return _isActive; }

	virtual bool start(const sf::Vector2f& distance, int time) {
		if (!_isActive) {
			init();
			_distance = distance;
			_elapsedTime = 0;
			_distanceTraveled = { 0.f, 0.f };
			_isPaused = false;
			_pausedTime = 0;
			_time = time;
			_clock.restart();
			_isActive = true;
			return true;
		}
		return false;
	}
	void update();
	virtual void init() { _isActive = false; }
	virtual void pause() { _isPaused = true; _pausedClock.restart(); }
	virtual void resume() { _isPaused = false; _pausedTime += _pausedClock.getElapsedTime().asMilliseconds(); }

	virtual ~Transition() = default;
};

namespace Transitions {
	class EaseInOut : public Transition {	// Quadratic
	private:
		sf::Vector2f _acc;	// max acceleration during rotation
		sf::Vector2f _velocity2;

		sf::Vector2f calcAcc(const sf::Vector2f& distance, int time) const { return distance / static_cast<float>(math::square(time / 2)); }
		sf::Vector2f calcVelocity2(const sf::Vector2f& acc, int time) const { return acc * static_cast<float>(time / 2); }

	public:
		explicit EaseInOut(Transitionable* object);

		bool start(const sf::Vector2f& distance, int time) override {
			if (!isActive()) {
				_acc = calcAcc(distance, time);
				_velocity2 = calcVelocity2(_acc, time);
				return Transition::start(distance, time);
			}
			return false;
		}
	};

	namespace Bezier {
		class Ease : public Transition {	// Cubic Bezier
		private:
			BezierEasing _bezier{ { 0.25f, 0.1f }, { 0.25f, 1.f } };

		public:
			explicit Ease(Transitionable* object);
		};
	}

	class Jump : public Transition {
	private:
		sf::Vector2f _acc;
		sf::Vector2f _velocity;

		sf::Vector2f calcAcc(const sf::Vector2f& distance, int time) const {
			return - 2.f * distance / math::squaref(static_cast<float>(time) / 2);
		}
		sf::Vector2f calcVelocity(const sf::Vector2f& acc, int time) const {
			return - acc / 2.f * static_cast<float>(time);
		}

	public:
		explicit Jump(Transitionable* object);

		bool start(const sf::Vector2f& distance, int time) override {
			if (!isActive()) {
				_acc = calcAcc(distance, time);
				_velocity = calcVelocity(_acc, time);
				return Transition::start(distance, time);
			}
			return false;
		}
	};
}
