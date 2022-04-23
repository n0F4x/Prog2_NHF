#pragma once
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>


namespace util {
	class string {
	private:
		char* _ptr = nullptr;
		std::size_t _size = 0;
	public:
		string() : string{ "" } {}
		string(const char* string) {
			_size = strlen(string) + 1;
			_ptr = new char[_size];
			strcpy(_ptr, string);
		}
		string(const string& other) : _size{other._size} {
			_ptr = new char[_size];
			strcpy(_ptr, other._ptr);
		}
		string& operator=(const string& other) {
			if (&other != this) {
				_size = other._size;
				delete[] _ptr;
				_ptr = new char[_size];
				strcpy(_ptr, other._ptr);
			}
			return *this;
		}

		auto operator<=>(const string& other) const {
			if (strcmp(_ptr, other._ptr) < 0) return -1;
			if (strcmp(_ptr, other._ptr) > 0) return 1;
			if (strcmp(_ptr, other._ptr) == 0) return 0;
			return 0;
		}

		~string() {
			delete[] _ptr;
		}
	};
}
