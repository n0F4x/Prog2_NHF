#include "MenuNode.hpp"

#include "Menu.hpp"


MenuNode::MenuNode(/*const std::string name, */std::unique_ptr<Menu> item, MenuNode* parent) :
	/*_name{ name }, */_item{ std::move(item) }, _parent{ parent } {}

void MenuNode::addChild(const std::string name, std::unique_ptr<Menu> child) { _children[name] = std::make_unique<MenuNode>(/*name, */std::move(child), this); }

Menu* MenuNode::get() { return _item.get(); }
MenuNode* MenuNode::getParent() { return _parent; }
std::map<const std::string, std::unique_ptr<MenuNode>>& MenuNode::getChildren() { return _children; }
