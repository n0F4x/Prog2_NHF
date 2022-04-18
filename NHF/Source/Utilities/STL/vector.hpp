#pragma once

#include <utility>


namespace util {
	template <typename T>
	class vector {
	public:
		class iterator;

	private:
		T* _vector = nullptr;
		std::size_t _size = 0;

	public:
		vector() {}

		template <typename... Args>
		void emplace_back(Args &&...args) {
			T* tmp = new T[_size + 1];
			for (std::size_t i = 0; i < _size; i++) {
				tmp[i] = std::move(_vector[i]);
			}
			tmp[_size] = std::move(T{ std::forward<Args>(args)... });
			_size++;
			delete[] _vector;
			_vector = tmp;
		}

		iterator begin() { return iterator(_vector, 0, _size); }
		iterator end() { return iterator(_vector, _size, _size); }

		~vector() {
			delete[] _vector;
		}

	public:
		class iterator {
		private:
			std::size_t _index = 0;
			std::size_t _size;
			T* _vector;

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
			bool operator==(iterator other) const { return _index == other._index; }
			bool operator!=(iterator other) const { return !(*this == other); }
			T& operator*() { return _vector[_index]; }
		};
	};
}
