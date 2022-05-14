#pragma once

#include <utility>


namespace util {
	template <typename T>
	class vector {
	public:
		class iterator;

	private:
		T* _ptr = nullptr;
		std::size_t _size = 0;

	public:
		vector() = default;
		vector(const vector&) = delete;
		vector& operator=(const vector&) = delete;

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

		iterator begin() { return iterator(_ptr, 0, _size); }
		iterator end() { return iterator(_ptr, _size, _size); }

		~vector() {
			delete[] _ptr;
		}

		// Iterator class for vector
		class iterator {
		private:
			T* _vector;
			std::size_t _index = 0;
			std::size_t _size;

		public:
			explicit iterator(T* vector, std::size_t index, std::size_t size) : _vector{ vector }, _index{ index }, _size{ size } {}
			iterator& operator++() {
				++_index;
				return *this;
			}
			iterator operator++(int) {
				iterator retval = *this;
				++(*this);
				return retval;
			}
			bool operator==(const iterator& other) const { return _index == other._index; }
			T& operator*() { return _vector[_index]; }
		};
	};
}
