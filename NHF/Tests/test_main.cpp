#ifdef CPORTA

#include "../Source/Utilities/STL/vector.hpp"
#include "gtest_lite.h"


void TEST_VECTOR() {
	TEST(util::vector::iterator, operator==()) {
		util::vector<int> vector;
		EXPECT_EQ(true, vector.begin() == vector.end());
	}
	END;
	TEST(util::vector::iterator, operator++()) {
		util::vector<int> vector;
		vector.emplace_back(3);
		auto it = vector.begin();
		EXPECT_EQ(false, it == vector.end());
		EXPECT_EQ(true, ++it == vector.end());
	}
	END;
	TEST(util::vector::iterator, operator++(int)) {
		util::vector<int> vector;
		vector.emplace_back(3);
		auto it = vector.begin();
		EXPECT_EQ(false, it++ == vector.end());
		EXPECT_EQ(true, it == vector.end());
	}
	END;
}


int main() {
	TEST_VECTOR();

	return 0;
}

#endif // CPORTA
