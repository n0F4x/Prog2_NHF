#pragma once

#include <functional>
#include <any>
#include <string>
#include <stdexcept>


class Context {
public:
	class ToStringConverter {
		const std::function<std::string(const std::any&)> _func;
	public:
		explicit(false) ToStringConverter(const std::function<std::string(const std::any&)>& func) : _func{ func } {}
		std::string operator()(const std::any& val) const { return _func(val); }
	};

	class Validator {
	private:
		std::function<bool(const std::any&)> _func;
	public:
		explicit(false) Validator(const std::function<bool(const std::any&)>& func = [](const std::any&) -> bool { return true; }) : _func{ func } {}
		bool operator()(const std::any& data) const { return _func(data); }
	};


private:
	std::any _data;
	const ToStringConverter _converter;
	const Validator _validator;

public:
	explicit Context(const std::any& data, const ToStringConverter& converter, const Validator& validator);

	template <typename T>
	T get() const { return std::any_cast<T>(_data); }

	std::string string() const { return _converter(_data); }

	template <typename T>
	std::string string(const T& val) const { return _converter(val); }

	bool set(const std::any& data);
	bool set(std::any&& data);

	bool validate(const std::any& potentialData) const { return _validator(potentialData); }
};
