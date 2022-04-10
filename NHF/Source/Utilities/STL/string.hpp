#pragma once
#pragma warning(disable : 4996)

#include <cstring>



namespace util {
	class string {
	private:
		char* _string = nullptr;
		std::size_t _size = 0;
	public:
		string(const char* string) {
			_size = strlen(string) + 1;
			_string = new char[_size];
			strcpy(_string, string);
		}
		string(const string& other) {
			_size = other._size;
			_string = new char[_size];
			strcpy(_string, other._string);
		}

		bool operator<(const string& other) const {
			return strcmp(_string, other._string) < 0;
		}

		~string() {
			delete[] _string;
		}
	};
}
