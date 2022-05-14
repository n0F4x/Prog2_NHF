#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "Context.hpp"


/**
 * @brief Enum class for type of platform control
*/
enum class PlatformControl {
	Keyboard,
	Mouse
};


/**
 * @brief	Class for accessing and writing contexts
*/
class ContextManager {
private:
	std::map<const std::string, Context, std::less<>> _contexts;
	/**
	 * @brief	Adds context to class
	 * @param name	Name of the new context
	 * @param initialValue	Initial value of the new context
	 * @param converter	ToStringConverter of the new context
	 * @param validator	Validator of the new context
	*/
	void addContext(
		const std::string& name,
		const std::any& initialValue,
		const Context::ToStringConverter& converter,
		const Context::Validator& validator = {}
	);

public:
	/**
	 * @brief	Fills container with pre-defined contexts
	*/
	ContextManager();

	/**
	 * @brief Tries reading contexts from file to class
	*/
	void loadFromFile();
	/**
	 * @brief Saves contexts to file
	*/
	void save();


	/**
	 * @brief	Searches context by name. Returns nullptr if not found
	 * @param name	Name of the searched context
	 * @return	Pointer to the desired context, nullptr if not found
	*/
	Context* find(const std::string_view& name);
};


/**
 * @brief	Compares two KeyEvents
 * @param lhs	Left hand side of operation
 * @param rhs	Right hand side of operation
 * @return	True if the are equal
*/
bool operator==(const sf::Event::KeyEvent& lhs, const sf::Event::KeyEvent& rhs);
