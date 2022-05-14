#ifdef CPORTA

#include "../Source/Utilities/STL/vector.hpp"
#include "../Source/Core/Controller/MenuNode.hpp"
#include "../Source/Menus/Menu.hpp"
#include "../Source/Menus/GameMenu/Player.hpp"
#include "../Source/Core/Controller.hpp"
#include "../Source/Core/AppData.hpp"

#include "gtest_lite.h"


void write_title() {
	std::cout << "\n";
	std::cout << "        ///      ///    ////    ///    ///    ///////////              ///////////    ///////////     ////////      ///////////     //////// \n";
	std::cout << "       ///      ///    /////   ///    ///        ///                      ///        ///            ///      //        ///        ///      //\n";
	std::cout << "      ///      ///    /// //  ///    ///        ///                      ///        ///////////      ///////          ///          ///////   \n";
	std::cout << "     ///      ///    ///  // ///    ///        ///                      ///        ///            //      ///        ///        //      ///  \n";
	std::cout << "       //////       ///   /////    ///        ///                      ///        ///////////      ////////         ///          ////////    \n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
}

template <class TestClass>
void test_class() { /* Use with specialization only */ }


template <>
void test_class<util::vector<int>>() {
	std::cout << "Testing util::vector:\n";

	TEST(operator==()) {
		util::vector<int> vector;
		EXPECT_EQ(true, vector.begin() == vector.end());
	}
	END;
	TEST(operator++()) {
		util::vector<int> vector;
		vector.emplace_back(3);
		auto it = vector.begin();
		EXPECT_EQ(false, it == vector.end());
		EXPECT_EQ(true, ++it == vector.end());
	}
	END;
	TEST(operator++(int)) {
		util::vector<int> vector;
		vector.emplace_back(3);
		auto it = vector.begin();
		EXPECT_EQ(false, it++ == vector.end());
		EXPECT_EQ(true, it == vector.end());
	}
	END;

	std::cout << "\n\n";
}

template <>
void test_class<PlayerSprite>() {
	std::cout << "Testing PlayerSprite:\n";

	TEST(getInitPos()) {
		EXPECT_EQ(true, sf::Vector2f{} == PlayerSprite{}.getInitPos());

		PlayerSprite playerSprite;
		playerSprite.setInitPos({ 1.f, 1.f });
		EXPECT_EQ(true, (sf::Vector2f{ 1.f, 1.f } == playerSprite.getInitPos()));
	}
	END;

	std::cout << "\n\n";
}

template <>
void test_class<Player>() {
	std::cout << "Testing Player:\n";

	TEST(getFeet()) {
		EXPECT_EQ(true, (sf::Vector2f{ 0.f, 30.f } == Player{}.getFeet()));
	}
	END;

	std::cout << "\n\n";
}

template <>
void test_class<MenuNode>() {
	std::cout << "Testing MenuNode:\n";

	TEST(get()) {
		EXPECT_EQ(true, nullptr == MenuNode{}.get());

		auto menu{ std::make_unique<Menu>() };
		auto menuPtr{ menu.get() };
		MenuNode menuNode{ std::move(menu) };
		EXPECT_EQ(true, menuPtr == menuNode.get());
	}
	END;
	TEST(getParent()) {
		EXPECT_EQ(true, nullptr == MenuNode{}.getParent());

		MenuNode parent;
		auto menu{ std::make_unique<Menu>() };
		MenuNode menuNode{ std::move(menu), &parent };
		EXPECT_EQ(true, &parent == menuNode.getParent());
	}
	END;
	TEST(findChild()) {
		MenuNode menuNode;
		menuNode.addChild("child", std::make_unique<Menu>());

		EXPECT_EQ(true, nullptr == menuNode.findChild("not found"));
		EXPECT_NE(true, nullptr == menuNode.findChild("child"));
	}
	END;
	TEST(getLastVisitedChild()) {
		EXPECT_EQ(true, nullptr == MenuNode{}.getLastVisitedChild());
	}
	END;
	TEST(setLastVisitedChild()) {
		MenuNode menuNode;
		menuNode.setLastVisitedChild(&menuNode);
		EXPECT_EQ(true, &menuNode == menuNode.getLastVisitedChild());
	}
	END;

	std::cout << "\n\n";
}

template <>
void test_class<Controller>() {
	std::cout << "Testing Controller:\n";

	TEST(isActive()) {
		AppData appData;
		appData.loadAssets();
		Window window;
		Controller controller{ window };
		controller.load();
		EXPECT_EQ(true, controller.isActive());
	}
	END;

	std::cout << "\n\n";
}


int main() {
	write_title();

	test_class<util::vector<int>>();
	test_class<MenuNode>();
	test_class<PlayerSprite>();
	test_class<Player>();
	test_class<Controller>();

	return 0;
}

#endif // CPORTA
