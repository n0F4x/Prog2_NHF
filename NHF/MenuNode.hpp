#pragma once

#include <map>
#include <string>
#include <memory>

#include "Menu.hpp"


class MenuNode {
private:
	//const std::string _name;
	std::unique_ptr<Menu> _item;
	MenuNode* _parent;
	std::map<const std::string, std::unique_ptr<MenuNode>> _children;

public:
	MenuNode(/*const std::string name, */std::unique_ptr<Menu> item, MenuNode* parent = nullptr);
	void addChild(const std::string name, std::unique_ptr<Menu> child);
	
	Menu* get();
	MenuNode* getParent();
	std::map<const std::string, std::unique_ptr<MenuNode>>& getChildren();
};

