#include "MenuNode.hpp"

#include "Menu.hpp"


MenuNode::MenuNode(std::unique_ptr<Menu> item, MenuNode* parent) :
	_item{ std::move(item) }, _parent{ parent } {}

void MenuNode::addChild(const util::string& name, std::unique_ptr<Menu> child) { _children[name] = std::make_unique<MenuNode>(std::move(child), this); }

Menu* MenuNode::get() { return _item.get(); }
MenuNode* MenuNode::getParent() { return _parent; }
std::map<const util::string, std::unique_ptr<MenuNode>>& MenuNode::getChildren() { return _children; }
