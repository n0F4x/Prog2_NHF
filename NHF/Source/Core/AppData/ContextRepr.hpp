#pragma once

#include "ContextManager.hpp"


template <typename T>
class ContextRepr {
private:
	T _dataRepr;
	Context* const _context;

public:
	ContextRepr() = delete;
	explicit ContextRepr<T>(Context* const context);
	ContextRepr<T>& operator=(const T& data);
	ContextRepr<T>& operator=(const T&& data);

	explicit (false) operator T() const { return _dataRepr; }
	explicit operator std::string() const { return _context->string(); }

	std::string string(const T& val) const { return _context->string(val); }
	bool validate(const T& potentialData) const { return _context->validate(potentialData); }

	void update() { _dataRepr = _context->get<T>(); }
};


template<typename T>
inline ContextRepr<T>::ContextRepr(Context* const context) : _context{ context } {
	if (_context == nullptr) {
		throw std::invalid_argument{ "ContextRepr construction failed, because pointer to context is invalid.\n" };
	}
	update();
}

template<typename T>
inline ContextRepr<T>& ContextRepr<T>::operator=(const T& data) {
	if (_context->set(data)) {
		_dataRepr = data;
	}
	return *this;
}

template<typename T>
inline ContextRepr<T>& ContextRepr<T>::operator=(const T&& data) {
	if (_context->set(data)) {
		_dataRepr = std::move(data);
	}
	return *this;
}
