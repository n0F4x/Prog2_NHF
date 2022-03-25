#pragma once

#include <memory>
#include <stack>

#include "Stage.hpp"


class StageManager {
private:
	std::stack<std::unique_ptr<Stage>> _stages;
	std::unique_ptr<Stage> _newStage;

	bool _isRemoving = false;
	bool _isAdding = false;
	bool _isReplacing = false;

public:
	StageManager() = default;
	StageManager(std::unique_ptr<Stage> initialStage);

	bool isEmpty();
	void processChanges();

	Stage& current();
	void addStage(std::unique_ptr<Stage> newStage, bool isReplacing = true);
	void removeStage();
};
