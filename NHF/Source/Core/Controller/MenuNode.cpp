#include "MenuNode.hpp"


void MenuNode::addChild(const std::string& name, std::unique_ptr<MenuBase> child) {
	_children.try_emplace(name, std::make_unique<MenuNode>(std::move(child), this));
}

MenuNode* MenuNode::findChild(const std::string_view& name) {
	if (auto it = _children.find(name); it != _children.end()) {
		return it->second.get();
	}
	return nullptr;
}
