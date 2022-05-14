#pragma once

#include <map>
#include <memory>
#include "MenuBase.hpp"


/**
 * @brief	Class for storing a menu and information about its location inside the menu tree
 *
 * @detailed	Stores pointer to its parent, and stores children locally. Keeps track of last visited child
*/
class MenuNode {
private:
	std::unique_ptr<MenuBase> _item;
	MenuNode* _parent = nullptr;
	std::map<const std::string, const std::unique_ptr<MenuNode>, std::less<>> _children;
	MenuNode* _lastVisitedChild = nullptr;

public:
	/**
	 * @brief	Constructs a new MenuNode storing nothing
	*/
	MenuNode() = default;
	/**
	 * @brief	Constructs a new MenuNode storing a menu given as parameter and setting the parent node
	 * @param item	Menu to be managed by node
	 * @param parent	Parent node of class
	*/
	MenuNode(std::unique_ptr<MenuBase> item, MenuNode* parent = nullptr) : _item{ std::move(item) }, _parent{ parent } {}

	/**
	 * @brief	Tries appending child to locals.
	 * @param name	Name of the child
	 * @param child	Menu of the child
	*/
	void addChild(const std::string& name, std::unique_ptr<MenuBase> child);

	/**
	 * @brief	Getter for the managed menu
	 * @return	Pointer to the managed menu
	*/
	MenuBase* get() const { return _item.get(); }
	/**
	 * @brief	Getter for parent node
	 * @return	Pointer to parent node
	*/
	MenuNode* getParent() const { return _parent; }
	/**
	 * @brief	Searches for child inside locals
	 * @param name	Name of the desired child
	 * @return	Pointer to the child. Nullptr if the child is not found
	*/
	MenuNode* findChild(const std::string_view& name);

	/**
	 * @brief	Getter for last visited child
	 * @return	Pointer to last visited child
	*/
	MenuNode* getLastVisitedChild() const { return _lastVisitedChild; }
	/**
	 * @brief	Setter for last visited child
	 * @param child	Pointer to last visited child
	*/
	void setLastVisitedChild(MenuNode* child) { _lastVisitedChild = child; }
};
