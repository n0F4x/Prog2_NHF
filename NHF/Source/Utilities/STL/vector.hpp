#pragma once

#include <utility>


namespace util {
	/**
	 * @brief	Container class for imitating std::vector. This implementation is not error prone, use wisely! Add new features when necessary.
	 * @tparam T	Type of the values stored inside the class
	*/
	template <typename T>
	class vector {
	public:
		class iterator;

	private:
		T* _ptr = nullptr;
		std::size_t _size = 0;

	public:
		/**
		 * @brief	Constructs a new vector that stores zero elements
		*/
		vector() = default;
		vector(const vector&) = delete;
		vector& operator=(const vector&) = delete;

		/**
		 * @brief	Appends a new element to the end of the container. The element is constructed in place
		 * @tparam ...Args	Types of arguments given as parameters
		 * @param ...args	Arguments to forward to the constructor of the element
		*/
		template <typename... Args>
		void emplace_back(Args &&...args) {
			auto* tmp = new T[_size + 1u];
			for (std::size_t i = 0; i < _size; i++) {
				tmp[i] = std::move(_ptr[i]);
			}
			tmp[_size++] = T{ std::forward<Args>(args)... };
			delete[] _ptr;
			_ptr = tmp;
		}

		/**
		 * @brief 	Returns an iterator to the first element of the vector. If the vector is empty, the returned iterator will be equal to end(). 
		 * @return	Iterator to the first element. 
		*/
		iterator begin() { return iterator(_ptr, 0, _size); }
		/**
		 * @brief 	Returns an iterator to the element following the last element of the vector.
		 * @return	Iterator to the element following the last element.
		*/
		iterator end() { return iterator(_ptr, _size, _size); }

		/*
		 * @brief	Deletes the contents of the class 
		*/
		~vector() {
			delete[] _ptr;
		}

		/**
		 * @brief	iterator class for vector
		*/
		class iterator {
		private:
			T* _vector;
			std::size_t _index = 0;
			std::size_t _size;

		public:
			/**
			 * @brief	Constructs a new iterator for a specific vector
			 * @param vector	Pointer to the first element of the vector
			 * @param index		Index of the n^th element
			 * @param size		Number of elements inside the vector
			*/
			explicit iterator(T* vector, std::size_t index, std::size_t size) : _vector{ vector }, _index{ index }, _size{ size } {}
			/**
			 * @brief	Pre-increments index stored inside the iterator
			 * @return	Reference to self
			*/
			iterator& operator++() {
				++_index;
				return *this;
			}
			/**
			 * @brief	Post-increments index stored inside the iterator
			 * @param  
			 * @return	Iterator equal to this before increment
			*/
			iterator operator++(int) {
				iterator retval = *this;
				++(*this);
				return retval;
			}
			/**
			 * @brief	Checks if the index of other is equal to the index of this
			 * @param other	Other iterator
			 * @return	True if the indexes are equal
			*/
			bool operator==(const iterator& other) const { return _index == other._index; }
			/**
			 * @brief	Looks for the element stored inside vector at the indexes position
			 * @return	Reference to element 
			*/
			T& operator*() { return _vector[_index]; }
		};
	};
}
