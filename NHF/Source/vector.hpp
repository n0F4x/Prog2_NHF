#pragma once

#include <utility>


namespace util {
	template <typename T>
	class vector {
	public:
		class iterator;

	private:
		T* _vector = nullptr;
		unsigned _size = 0;

	public:
		vector() = default;
		vector(const vector&) = delete;
		vector& operator=(const vector&) = delete;

		template <typename... Args>
		void emplace_back(Args &&...args) {
			auto* tmp = new T[_size + 1u];
			for (unsigned i = 0; i < _size; i++) {
				tmp[i] = std::move(_vector[i]);
			}
			tmp[_size++] = std::move(T{ std::forward<Args>(args)... });
			delete[] _vector;
			_vector = tmp;
		}

		iterator begin() { return iterator(_vector, 0, _size); }
		iterator end() { return iterator(_vector, _size, _size); }

		~vector() {
			delete[] _vector;
		}

		// Iterator class for vector
		class iterator {
		private:
			T* _vector;
			unsigned _index = 0;
			unsigned _size;

		public:
			explicit iterator(T* vector, unsigned index, unsigned size) : _vector{ vector }, _index{ index }, _size{ size } {}
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
			bool operator!=(iterator other) const { return _index != other._index; }
			T& operator*() { return _vector[_index]; }
		};
	};
}
