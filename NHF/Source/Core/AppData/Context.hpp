#pragma once

#include <functional>
#include <any>
#include <string>
#include <stdexcept>


class ToStringConverter {
	const std::function<std::string(const std::any&)> _func;
public:
	explicit(false) ToStringConverter(const std::function<std::string(const std::any&)>& func) : _func{ func } {}
	std::string operator()(const std::any& val) const { return _func(val); }
};


class Context {
public:
	class Validator {
	private:
		std::function<bool(const std::any&)> _func;
	public:
		explicit(false) Validator(const std::function<bool(const std::any&)>& func = [](const std::any&) -> bool { return true; }) : _func{ func } {}
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
			if (validate(data)) {
				_observable->_data = data;
				return true;
			}
			return false;
		}
		bool setContext(std::any&& data) const {
			if (validate(data)) {
				_observable->_data = std::move(data);
				return true;
			}
			return false;
		}
		bool validate(const std::any& data) const { return _observable->validate(data); }
	};

	friend Accessor;


private:
	std::any _data;
	const ToStringConverter _converter;
	const Validator _validator;

	bool validate(const std::any& data) const { return _validator(data); }

public:
	explicit Context(const std::any& data, const ToStringConverter& converter, const Validator& validator) :
		_data{ data }, _converter{ converter }, _validator{ validator } {}
	Accessor get() { return Accessor{ this }; }
};
