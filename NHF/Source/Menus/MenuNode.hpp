#pragma once

#include <map>
#include <memory>
#include "../Utilities/STL/string.hpp"
#include "Menu.hpp"


class MenuNode {
private:
	std::unique_ptr<Menu> _item;
	MenuNode* _parent;
	std::map<const util::string, std::unique_ptr<MenuNode>> _children;

public:
	MenuNode(std::unique_ptr<Menu> item, MenuNode* parent = nullptr);
	void addChild(const util::string& name, std::unique_ptr<Menu> child);
	
	Menu* get();
	MenuNode* getParent();
	std::map<const util::string, std::unique_ptr<MenuNode>>& getChildren();

	MenuNode* _lastVisitedChild = nullptr;
};

