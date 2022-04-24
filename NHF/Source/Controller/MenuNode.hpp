#pragma once

#include <map>
#include <memory>
#include "../Utilities/STL/string.hpp"
#include "MenuBase.hpp"


class MenuNode {
private:
	std::unique_ptr<MenuBase> _item;
	MenuNode* _parent = nullptr;
	std::map<const util::string, std::unique_ptr<MenuNode>> _children;
	MenuNode* _lastVisitedChild = nullptr;

public:
	MenuNode() = default;
	MenuNode(std::unique_ptr<MenuBase> item, MenuNode* parent = nullptr) : _item{ std::move(item) }, _parent{ parent } {}

	void addChild(const util::string& name, std::unique_ptr<MenuBase> child) { _children[name] = std::make_unique<MenuNode>(std::move(child), this); }
	
	MenuBase* get() const { return _item.get(); }
	MenuNode* getParent() const { return _parent; }
	MenuNode* findChild(const util::string& name) { 
		if (auto it = _children.find(name); it != _children.end()) {
			return it->second.get();
		}
		return nullptr;
	}

	MenuNode* getLastVisitedChild() const { return _lastVisitedChild; }
	void setLastVisitedChild(MenuNode* child) { _lastVisitedChild = child; }
};
