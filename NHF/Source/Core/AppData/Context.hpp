#pragma once

#include <functional>
#include <any>
#include <string>


/**
 * @brief Class for storing data inside ContextManager
*/
class Context {
public:
	/**
	 * @brief Functor for converting Context data to string
	*/
	class ToStringConverter {
		const std::function<std::string(const std::any&)> _func;
	public:
		/**
		 * @brief	Constructs new converter
		 * @param func	Inside-function of the functor class
		*/
		explicit(false) ToStringConverter(const std::function<std::string(const std::any&)>& func) : _func{ func } {}
		/**
		 * @brief	Calls function stored inside class
		 * @param val	Value to be given to function as param
		 * @return	Result of calling the inside-function
		*/
		std::string operator()(const std::any& val) const { return _func(val); }
	};

	/**
	 * @brief Functor for validating Context data
	*/
	class Validator {
	private:
		std::function<bool(const std::any&)> _func;
	public:
		/**
		 * @brief	Constructs new validator
		 * @param func	Inside-function of the functor class
		*/
		explicit(false) Validator(const std::function<bool(const std::any&)>& func = [](const std::any&) -> bool { return true; }) : _func{ func } {}
		/**
		 * @brief	Calls function stored inside class
		 * @param val	Value to be given to function as param
		 * @return	True if data is valid
		*/
		bool operator()(const std::any& data) const { return _func(data); }
	};


private:
	std::any _data;
	const ToStringConverter _converter;
	const Validator _validator;

public:
	/**
	 * @brief	Constructs new context
	 * @param data	Data managed by class
	 * @param converter	Functor for converting data to string
	 * @param validator Functor for validating new data
	*/
	explicit Context(const std::any& data, const ToStringConverter& converter, const Validator& validator);

	/**
	 * @brief	Getter for data. Throws bad_any_cast if template parameter is not the actual type of the data store inside the class
	 * @tparam T	Type of data
	 * @return	Data
	*/
	template <typename T>
	T get() const { return std::any_cast<T>(_data); }

	/**
	 * @brief	Converts data stored inside class to string
	 * @return	Result of conversion
	*/
	std::string string() const { return _converter(_data); }

	/**
	 * @brief	Uses the classes converter to try and convert the value given as parameter to string. 
			Throws bad_any_cast if template parameter is not the actual type of the data store inside the class
	 * @tparam T	Type of the given value
	 * @param val	Value to be converted
	 * @return	Result of conversion
	*/
	template <typename T>
	std::string string(const T& val) const { return _converter(val); }

	/**
	 * @brief	Validates and sets data inside class to the data given as parameter
	 * @param data	New data
	 * @return	Result of validation
	*/
	bool set(const std::any& data);
	/**
	 * @brief	Validates and sets data inside class to the data given as parameter
	 * @param data	New data
	 * @return	Result of validation
	*/
	bool set(std::any&& data);

	/**
	 * @brief	Performs validation on the potential new data given as parameter
	 * @param potentialData	Potential context data for validation
	 * @return	Result of validation
	*/
	bool validate(const std::any& potentialData) const { return _validator(potentialData); }
};
