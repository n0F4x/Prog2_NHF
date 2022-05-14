#ifdef CPORTA

#include "../Source/Utilities/STL/vector.hpp"
#include "../Source/Menus/GameMenu/Player.hpp"
#include "../Source/Core/Controller.hpp"
#include "../Source/Menus/Menu.hpp"
#include "../Source/Core/AppData.hpp"
#include "../Source/Menus/MainMenu.hpp"
#include "../Source/Menus/GameMenu.hpp"
#include "../Source/Menus/OptionsMenu.hpp"

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

	TEST(operator==(), ) {
		util::vector<int> vector;
		EXPECT_EQ(true, vector.begin() == vector.end());
	}
	END
		TEST(operator++(), ) {
		util::vector<int> vector;
		vector.emplace_back(3);
		auto it = vector.begin();
		EXPECT_EQ(false, it == vector.end());
		EXPECT_EQ(true, ++it == vector.end());
	}
	END
		TEST(operator++(int), ) {
		util::vector<int> vector;
		vector.emplace_back(3);
		auto it = vector.begin();
		EXPECT_EQ(false, it++ == vector.end());
		EXPECT_EQ(true, it == vector.end());
	}
	END

		std::cout << "\n\n";
}

template <>
void test_class<PlayerSprite>() {
	std::cout << "Testing PlayerSprite:\n";

	TEST(getInitPos(), ) {
		EXPECT_EQ(true, sf::Vector2f{} == PlayerSprite{}.getInitPos());

		PlayerSprite playerSprite;
		playerSprite.setInitPos({ 1.f, 1.f });
		EXPECT_EQ(true, (sf::Vector2f{ 1.f, 1.f } == playerSprite.getInitPos()));
	}
	END

		std::cout << "\n\n";
}

template <>
void test_class<Player>() {
	std::cout << "Testing Player:\n";

	TEST(getFeet(), ) {
		EXPECT_EQ(true, (sf::Vector2f{ 0.f, 30.f } == Player{}.getFeet()));
	}
	END

		std::cout << "\n\n";
}

template<>
void test_class<ContextManager>() {
	std::cout << "Testing ContextManager:\n";

	TEST(find(), ) {
		ContextManager manager;
		EXPECT_EQ(true, nullptr == manager.find("not found"));
		EXPECT_NE(true, nullptr == manager.find("speed"));
	}
	END

		std::cout << "\n\n";
}

template <>
void test_class<MenuNode>() {
	std::cout << "Testing MenuNode:\n";

	TEST(get(), ) {
		EXPECT_EQ(true, nullptr == MenuNode{}.get());

		auto menu{ std::make_unique<Menu>() };
		auto menuPtr{ menu.get() };
		MenuNode menuNode{ std::move(menu) };
		EXPECT_EQ(true, menuPtr == menuNode.get());
	}
	END
		TEST(getParent(), ) {
		EXPECT_EQ(true, nullptr == MenuNode{}.getParent());

		MenuNode parent;
		auto menu{ std::make_unique<Menu>() };
		MenuNode menuNode{ std::move(menu), &parent };
		EXPECT_EQ(true, &parent == menuNode.getParent());
	}
	END
		TEST(findChild(), ) {
		MenuNode menuNode;
		menuNode.addChild("child", std::make_unique<Menu>());

		EXPECT_EQ(true, nullptr == menuNode.findChild("not found"));
		EXPECT_NE(true, nullptr == menuNode.findChild("child"));
	}
	END
		TEST(getLastVisitedChild(), ) {
		EXPECT_EQ(true, nullptr == MenuNode{}.getLastVisitedChild());
	}
	END
		TEST(setLastVisitedChild(), ) {
		MenuNode menuNode;
		menuNode.setLastVisitedChild(&menuNode);
		EXPECT_EQ(true, &menuNode == menuNode.getLastVisitedChild());
	}
	END

		std::cout << "\n\n";
}

template <>
void test_class<Controller>() {
	std::cout << "Testing Controller:\n";

	TEST(isActive(), ) {
		AppData appData;
		appData.loadAssets();
		Window window;
		Controller controller{ window };
		controller.load();
		EXPECT_EQ(true, controller.isActive());
	}
	END

		std::cout << "\n\n";
}


void run_comprehensive_test_1() {
	std::cout << "Running comprehensive test #1\n...\n";

	try {
		MainMenu mainMenu;
		mainMenu.init();
		mainMenu.update();
		mainMenu.pause();
		mainMenu.resume();
		mainMenu.render();

		GameMenu gameMenu;
		gameMenu.init();
		gameMenu.update();
		gameMenu.pause();
		gameMenu.resume();
		gameMenu.render();

		OptionsMenu optionsMenu;
		optionsMenu.init();
		optionsMenu.update();
		optionsMenu.pause();
		optionsMenu.resume();
		optionsMenu.render();


		std::cout << "Success!\n\n\n";
	}
	catch (const std::exception& e) {
		std::cout << "Failure!\n";
		std::cout << "Message:\t" << e.what();
	}
}

void run_comprehensive_test_2() {
	std::cout << "Running comprehensive test #2\n...\n";

	try {
		AppData appData;
		Window window;
		Controller controller{ window };

		appData.loadAssets();
		controller.load();
		appData.loadContexts();
		for (int iter = 0; controller.isActive() && iter < 60 * 3; iter++) {
			controller->update();
			controller->render();
			window.lockFPS();
		}
		appData.save();


		std::cout << "Success!\n\n\n";
	}
	catch (const std::exception& e) {
		std::cout << "Failure!\n";
		std::cout << "Message:\t" << e.what();
	}
}


int main() {
	write_title();

	test_class<util::vector<int>>();
	test_class<PlayerSprite>();
	test_class<Player>();
	test_class<ContextManager>();
	test_class<MenuNode>();
	test_class<Controller>();

	run_comprehensive_test_1();
	run_comprehensive_test_2();

	return 0;
}

#endif // CPORTA
