#include "StageManager.hpp"


void StageManager::addStage(std::unique_ptr<Stage> newStage, bool isReplacing) {
	_isAdding = true;
	_isReplacing = isReplacing;

	_newStage = std::move(newStage);
}

void StageManager::removeStage() {
	_isRemoving = true;
}

StageManager::StageManager(std::unique_ptr<Stage> initialStage) {
	_stages.push(std::move(initialStage));
}

bool StageManager::isEmpty() {
	return _stages.empty();
}

void StageManager::processChanges() {
	if (_isRemoving) {
		if (!_stages.empty()) {
			_stages.pop();

			if (!_stages.empty()) {
				_stages.top()->resume();
			}
		}
		_isRemoving = false;
	}

	if (_isAdding) {
		if (!_stages.empty()) {
			if (_isReplacing)
				_stages.pop();
			else
				_stages.top()->pause();
		}

		_stages.push(std::move(_newStage));
		_isAdding = false;
	}
}

Stage& StageManager::current() {
	return *_stages.top();
}
