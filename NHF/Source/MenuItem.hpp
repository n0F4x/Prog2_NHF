#pragma once

#include <vector>
#include "SFMLDrawable.hpp"
#include "SFMLEvent.hpp"
#include "Transitions.hpp"


class MenuItem : public sf::Drawable {
private:
	bool _isPaused = false;

	std::vector<Transition*> _transitions;

protected:
	bool isPaused() const { return _isPaused; }

	void addTransition(Transition* transition) { _transitions.push_back(transition); }

public:
	virtual void handleEvent(const sf::Event& event) { /*not pure*/ }
	virtual void update() { 
		for (auto it : _transitions) {
			it->update();
		}
	}
	virtual void init() { 
		for (auto it : _transitions) {
			it->init();
		}
		_isPaused = false;
	}
	virtual void pause() { 
		for (auto it : _transitions) {
			it->pause();
		}
		_isPaused = true;
	}
	virtual void resume() {
		for (auto it : _transitions) {
			it->resume();
		}
		_isPaused = false;
	}
};

