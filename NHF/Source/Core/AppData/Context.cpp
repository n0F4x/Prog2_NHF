#include "Context.hpp"

Context::Context(const std::any& data, const ToStringConverter& converter, const Validator& validator) :
	_data{ data }, _converter{ converter }, _validator{ validator } {}


bool Context::set(const std::any& data) {
	if (_validator(data)) {
		_data = data;
		return true;
	}
	return false;
}

bool Context::set(std::any&& data) {
	if (_validator(data)) {
		_data = std::move(data);
		return true;
	}
	return false;
}
