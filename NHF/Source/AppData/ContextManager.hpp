#pragma once

#include <functional>
#include <any>
#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>


class ToStringConverter {
	const std::function<std::string(const std::any&)> _func;
public:
	explicit(false) ToStringConverter(const std::function<std::string(const std::any&)>& func) : _func{ func } {}
	std::string operator()(const std::any& val) const { return _func(val); }
};


class Context {
public:
	class ValidatorBase {
	private:
		std::function<bool(const std::any&)> _func;
	public:
		explicit(false) ValidatorBase(const std::function<bool(const std::any&)>& func = [](const std::any&) -> bool { return true; }) : _func{ func } {}
		bool operator()(const std::any& data) const { return _func(data); }
	};

	class Accessor {
	private:
		Context* const _observable;

	public:
		explicit Accessor(Context* observable = nullptr) : _observable{ observable } {}
		explicit(false) operator bool() const { return _observable != nullptr; }
		const std::any& getContext() const { return _observable->_data; }
		std::string getContextString() const { return _observable->_converter(_observable->_data); }
		bool setContext(const std::any& data) const {
			if (_observable->validate(data)) {
				_observable->_data = data;
				std::cout << "true";
				return true;
			}
			std::cout << "false";
			return false;
		}
		bool setContext(std::any&& data) const {
			if (_observable->validate(data)) {
				_observable->_data = std::move(data);
				std::cout << "true";
				return true;
			}
			std::cout << "false";
			return false;
		}
	};
	friend Accessor;

private:
	std::any _data;
	const std::unique_ptr<const ValidatorBase> _validator;
	const ToStringConverter _converter;

	bool validate(const std::any& data) const { return (*_validator)(data); }

public:
	explicit Context(const std::any& data, const ValidatorBase* const validator, const ToStringConverter& converter) :
		_data{ data }, _validator{ validator }, _converter{ converter } {}
	Accessor get() { return Accessor{ this }; }
};



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

	void addContext(const std::string& name, const std::any& initialValue, Context::ValidatorBase* validator, const ToStringConverter& converter);

public:
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
