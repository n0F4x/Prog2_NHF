#pragma once

#include "ContextManager.hpp"


template <typename T>
class ContextRepr {
private:
	T _dataRepr;
	Context* _context;

public:
	ContextRepr() = delete;
	explicit ContextRepr<T>(Context* const context) : _context{ context } {
		if (_context == nullptr) {
			throw std::invalid_argument{ "ContextRepr construction failed, because pointer to context is invalid.\n" };
		}
		update();
	}
	ContextRepr<T>& operator=(const T& data) {
		if (_context->set(data)) {
			_dataRepr = data;
		}
		return *this;
	}
	ContextRepr<T>& operator=(const T&& data) {
		if (_context->set(data)) {
			_dataRepr = std::move(data);
		}
		return *this;
	}
	void update() {
		_dataRepr = _context->get<T>();
	}
	std::string string(const T& val) { return _context->string(val); }
	bool validate(const T& potentialData) { return _context->validate(potentialData); }
	explicit (false) operator T() const { return _dataRepr; }
	explicit operator std::string() const { return _context->string(); }
};
