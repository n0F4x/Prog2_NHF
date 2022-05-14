#pragma once

#include <map>
#include <memory>
#include "MenuBase.hpp"


class MenuNode {
private:
	std::unique_ptr<MenuBase> _item;
	MenuNode* _parent = nullptr;
	std::map<const std::string, const std::unique_ptr<MenuNode>, std::less<>> _children;
	MenuNode* _lastVisitedChild = nullptr;

public:
	MenuNode() = default;
	MenuNode(std::unique_ptr<MenuBase> item, MenuNode* parent = nullptr) : _item{ std::move(item) }, _parent{ parent } {}

	void addChild(const std::string& name, std::unique_ptr<MenuBase> child) {
		_children.try_emplace(name, std::make_unique<MenuNode>(std::move(child), this));
	}

	MenuBase* get() const { return _item.get(); }
	MenuNode* getParent() const { return _parent; }
	MenuNode* findChild(const std::string_view& name) {
		if (auto it = _children.find(name); it != _children.end()) {
			return it->second.get();
		}
		return nullptr;
	}

	MenuNode* getLastVisitedChild() const { return _lastVisitedChild; }
	void setLastVisitedChild(MenuNode* child) { _lastVisitedChild = child; }
};
