#pragma once

#include "ContextManager.hpp"


template <typename T>
class ContextRepr {
private:
	T _dataRepr;
	Context::Accessor _access;

public:
	ContextRepr() = delete;
	explicit ContextRepr<T>(const Context::Accessor& access) : _access{ access } {
		if (!_access) {
			throw std::invalid_argument{ "ContextRepr construction failed, because accessor is invalid.\n" };
		}
		update();
	}
	ContextRepr<T>& operator=(const T& data) {
		if (_access.setContext(data)) {
			_dataRepr = data;
		}
		return *this;
	}
	ContextRepr<T>& operator=(const T&& data) {
		if (_access.setContext(data)) {
			_dataRepr = std::move(data);
		}
		return *this;
	}
	void update() {
		_dataRepr = std::any_cast<T>(_access.getContext());
	}
	bool validate(const T& potentialData) { return _access.validate(potentialData); }
	explicit (false) operator T() const { return _dataRepr; }
	explicit operator std::string() const { return _access.getContextString(); }
};
