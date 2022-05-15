#pragma once

#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Transitionable.hpp"
#include "BezierEasing.hpp"
#include "../Math.hpp"


/**
 * @brief	Class for performing transition on a given
*/
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
	/**
	 * @brief	Constructs a new Transiton
	 * @param object	The object of the transition
	 * @param getProgression	Function to calculate the progress of the transition from 0 to t interval
	 * @param correctDistance	Function to correct the left-over transition amount from 0 to t
	*/
	explicit Transition(
		Transitionable* object,
		const std::function<sf::Vector2f(int elapsedTime)>& getProgression,
		const std::function<sf::Vector2f()>& correctDistance = nullptr
	);

	/**
	 * @brief	Gets the duration time of the transition
	 * @return	The duration time of the transition
	*/
	int getDurationTime() const { return _time; }
	/**
	 * @brief	Gets the duration distance of the transition
	 * @return	The duration distance of the transition
	*/
	const sf::Vector2f& getDurationDistance() const { return _distance; }
	/**
	 * @brief	Gets the time elapsed since the beginning of the current transition
	 * @return	The elapsed time
	*/
	int getElapsedTime() const { return _elapsedTime; }
	/**
	 * @brief	Gets the extent of the distance travelled since the beginning of the current transition
	 * @return	The travelled distance
	*/
	const sf::Vector2f& getDistanceTraveled() const { return _distanceTraveled; }

public:
	/**
	 * @brief	Checks whether the transition is still happening
	 * @return	True if it the object is in transition mode
	*/
	bool isActive() const { return _isActive; }

	/**
	 * @brief	Starts the transition if it is not active
	 * @param distance	The overall distance of the transition
	 * @param time	The overall time of the transition
	 * @return	True if the transition could be started
	*/
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
	/**
	 * @brief	Updates the transition's process and does the transitioning
	*/
	void update();
	/**
	 * @brief	Initializes the Transition, making it inactive
	*/
	virtual void init() { _isActive = false; }
	/**
	 * @brief	Paused the transition
	*/
	virtual void pause() { _isPaused = true; _pausedClock.restart(); }
	/**
	 * @brief	Resumes the transition
	*/
	virtual void resume() { _isPaused = false; _pausedTime += _pausedClock.getElapsedTime().asMilliseconds(); }

	/**
	 * @brief	Default virtual destructor
	*/
	virtual ~Transition() = default;
};

/**
 * @brief	Specialized transitions
*/
namespace Transitions {
	/**
	 * @brief	Class for performing physics-like quadratic transitions (accelerate, then break)
	*/
	class EaseInOut : public Transition {
	private:
		sf::Vector2f _acc;	// max acceleration during transition
		sf::Vector2f _velocity2;

		sf::Vector2f calcAcc(const sf::Vector2f& distance, int time) const { return distance / static_cast<float>(math::square(time / 2)); }
		sf::Vector2f calcVelocity2(const sf::Vector2f& acc, int time) const { return acc * static_cast<float>(time / 2); }

	public:
		/**
		 * @brief	Constructs a new EaseInOut transition for the given object
		 * @param object 
		*/
		explicit EaseInOut(Transitionable* object);

		/**
		 * @brief	Starts the transition if it is not active
		 * @param distance	The overall distance of the transition
		 * @param time	The overall time of the transition
		 * @return	True if the transition could be started
		*/
		bool start(const sf::Vector2f& distance, int time) override {
			if (!isActive()) {
				_acc = calcAcc(distance, time);
				_velocity2 = calcVelocity2(_acc, time);
				return Transition::start(distance, time);
			}
			return false;
		}
	};

	/**
	 * @brief	Cubic Bezier transitions
	*/
	namespace Bezier {
		/**
		 * @brief	Transition class for cubic Bezier easing
		*/
		class Ease : public Transition {
		private:
			BezierEasing _bezier{ { 0.25f, 0.1f }, { 0.25f, 1.f } };

		public:
			/**
			 * @brief	Construct a new Ease
			 * @param object	The object of the transition
			*/
			explicit Ease(Transitionable* object);
		};
	}

	/**
	 * @brief	Transition class for jumping transition
	*/
	class Jump : public Transition {
	private:
		sf::Vector2f _acc;
		sf::Vector2f _velocity;

		/**
		 * @brief	Calculates the acceleration of the transition
		 * @param distance	The overall distance of the transition
		 * @param time	The overall time of the transition
		 * @return	The acceleration of the transition
		*/
		sf::Vector2f calcAcc(const sf::Vector2f& distance, int time) const {
			return - 2.f * distance / math::squaref(static_cast<float>(time) / 2);
		}
		/**
		 * @brief	Calculates the initial velocitiy of the transition
		 * @param distance	The overall distance of the transition
		 * @param time	The overall time of the transition
		 * @return	The initial velocitiy of the transition
		*/
		sf::Vector2f calcVelocity(const sf::Vector2f& acc, int time) const {
			return - acc / 2.f * static_cast<float>(time);
		}

	public:
		/**
		 * @brief	Constructs a new Jump
		 * @param object	The object of the transition
		*/
		explicit Jump(Transitionable* object);

		/**
		 * @brief	Starts the transition if it is not active
		 * @param distance	The overall distance of the transition
		 * @param time	The overall time of the transition
		 * @return	True if the transition could be started
		*/
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
