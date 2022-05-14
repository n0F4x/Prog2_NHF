#pragma once

#include "ContextManager.hpp"


/**
 * @brief	Class for representing a context of ContextManager. Stores a copy of data inside context that may not be up-to-date
 * @tparam T	Type of data inside context. Incorrect data type can cause undefined behaviour
*/
template <typename T>
class ContextRepr {
private:
	T _dataRepr;
	Context* const _context;

public:
	ContextRepr() = delete;
	/**
	 * @brief	Constructs new representation of a context
	 * @param context	Pointer to the desired context to be represented
	*/
	explicit ContextRepr<T>(Context* const context);
	/**
	 * @brief	Calls set(copy) on the context with argument given as parameter. Updates data represented locally
	 * @param data	Potential new data of context
	 * @return	Reference to this
	*/
	ContextRepr<T>& operator=(const T& data);
	/**
	 * @brief	Calls set(move) on the context with argument given as parameter. Updates data represented locally
	 * @param data	Potential new data of context
	 * @return	Reference to this
	*/
	ContextRepr<T>& operator=(const T&& data);

	/**
	 * @brief	Default cast to of represented data to type T. No actual casting is performed. Returns data stored inside class
	*/
	explicit (false) operator T() const { return _dataRepr; }
	/**
	 * @brief	Calls string function of context
	*/
	explicit operator std::string() const { return _context->string(); }

	/**
	 * @brief	Equivalent to Context::string()
	 * @param val	Value to be converted
	 * @return	Result of string conversion
	*/
	std::string string(const T& val) const { return _context->string(val); }
	/**
	 * @brief	Equivalent to Context::validate()
	 * @param potentialData	Value for validation
	 * @return	True if the validation was successful
	*/
	bool validate(const T& potentialData) const { return _context->validate(potentialData); }

	/**
	 * @brief Fetches and updates data stored inside class
	*/
	void update() { _dataRepr = _context->get<T>(); }
};


/////////////////
// Definitions //
/////////////////

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
