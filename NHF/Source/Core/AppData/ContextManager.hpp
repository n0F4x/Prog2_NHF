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
	friend AppData;
	ContextManager();

	std::map<const std::string, Context, std::less<>> _contexts;

	void addContext(const std::string& name, const std::any& initialValue, const ToStringConverter& converter, const Context::Validator& validator = {});

	void loadFromFile() const { /*TODO*/ }
	void save() const { /*TODO*/ }

	Context::Accessor getContext(const std::string_view& name) {
		if (auto it = _contexts.find(name); it != _contexts.end()) {
			return it->second.get();
		}
		return Context::Accessor{};
	}
};


bool operator==(const sf::Event::KeyEvent& lhs, const sf::Event::KeyEvent& rhs);
