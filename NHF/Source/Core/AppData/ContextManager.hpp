#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "Context.hpp"


class AppData;


enum class PlatformControl {
	Keyboard,
	Mouse
};


class ContextManager {
private:
	std::map<const std::string, Context, std::less<>> _contexts;
	void addContext(
		const std::string& name,
		const std::any& initialValue,
		const Context::ToStringConverter& converter,
		const Context::Validator& validator = {}
	);


	friend AppData;
	ContextManager();

	void loadFromFile() const { /*TODO*/ }
	void save() const { /*TODO*/ }

	Context* find(const std::string_view& name);
};


bool operator==(const sf::Event::KeyEvent& lhs, const sf::Event::KeyEvent& rhs);
