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
	std::cout << "           ///////////    ///////////     ////////      ///////////     //////// \n";
	std::cout << "              ///        ///            ///      //        ///        ///      //\n";
	std::cout << "             ///        ///////////      ///////          ///          ///////   \n";
	std::cout << "            ///        ///            //      ///        ///        //      ///  \n";
	std::cout << "           ///        ///////////      ////////         ///          ////////    \n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
}


////////////////
// Unit tests //
////////////////

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

    AppData appData{};
    appData.loadAssets();

    TEST(getInitPos(), ) {
		EXPECT_EQ(true, sf::Vector2f{} == PlayerSprite{}.getInitPos());

		PlayerSprite playerSprite;
		playerSprite.setInitPos({ 1.f, 1.f });
		EXPECT_EQ(true, (sf::Vector2f{ 1.f, 1.f } == playerSprite.getInitPos()));
	}
	END

    appData.cleanUp();

		std::cout << "\n\n";
}

template <>
void test_class<Player>() {
	std::cout << "Testing Player:\n";

    AppData appData{};
    appData.loadAssets();

    TEST(getFeet(), ) {
		EXPECT_EQ(true, (sf::Vector2f{ 0.f, 30.f } == Player{}.getFeet()));
	}
	END

    appData.cleanUp();

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
        appData.cleanUp();
	}
	END

		std::cout << "\n\n";
}

/////////////////////
// Integrity tests //
/////////////////////

void run_comprehensive_test_1() {
	std::cout << "Running comprehensive test #1\n...\n";

    AppData appData;
    appData.loadAssets();

	try {
		sf::Event event;
		MainMenu mainMenu;
		mainMenu.init();
		mainMenu.handleEvent(event);
		mainMenu.update();
		mainMenu.pause();
		mainMenu.resume();
		mainMenu.render();

		GameMenu gameMenu;
		gameMenu.init();
		gameMenu.handleEvent(event);
		gameMenu.update();
		gameMenu.pause();
		gameMenu.resume();
		gameMenu.render();

		OptionsMenu optionsMenu;
		optionsMenu.init();
		optionsMenu.handleEvent(event);
		optionsMenu.update();
		optionsMenu.pause();
		optionsMenu.resume();
		optionsMenu.render();


		std::cout << "Success!\n";
	}
	catch (const std::exception& e) {
		std::cout << "Failure!\n";
		std::cout << "Message:\t" << e.what();
	}

    appData.cleanUp();

	std::cout << "\n\n";
}

void run_comprehensive_test_2() {
	std::cout << "Running comprehensive test #2\n...\n";

	try {
		AppData appData;
		Window window;
		Controller controller{ window };
		sf::Event event;

		appData.loadAssets();
		controller.load();
		appData.loadContexts();
		for (int iter = 0; controller.isActive() && iter < 2; iter++) {
			controller->handleEvent(event);
			controller->update();
			controller->render();
			window.lockFPS();
		}
        window.cleanUp();
		appData.save();
        appData.cleanUp();


		std::cout << "Success!\n";
	}
	catch (const std::exception& e) {
		std::cout << "Failure!\n";
		std::cout << "Message:\t" << e.what();
	}
	std::cout << "\n\n";
}

/////////////////
// Simulations //
/////////////////

void simulation_1() {
	std::cout << "Running simulation #1\n...\n";

	try {
		AppData appData;
		Window window;
		Controller controller{ window };

		std::vector<sf::Event> events{50};
		auto eventIter = events.begin();
		eventIter->type = sf::Event::KeyPressed;
		eventIter->key.code = sf::Keyboard::Num2;
		eventIter++;
		eventIter->type = sf::Event::MouseButtonPressed;
		eventIter->mouseButton = {sf::Mouse::Left, static_cast<int>(Window::getSize().x / 2.f), static_cast<int>(Window::getSize().y / 2.f)};
		eventIter++;
		eventIter->type = sf::Event::KeyPressed;
		eventIter->key.code = sf::Keyboard::A;
		eventIter++;
		eventIter->type = sf::Event::KeyReleased;
		eventIter->key.code = sf::Keyboard::A;
		eventIter++;
		eventIter->type = sf::Event::MouseButtonPressed;
		eventIter->mouseButton = { sf::Mouse::Left, 1750, 970 };
		eventIter++;
		eventIter->type = sf::Event::KeyPressed;
		eventIter->key.code = sf::Keyboard::Left;
		eventIter->key.alt = true;
		eventIter++;
		eventIter->type = sf::Event::KeyPressed;
		eventIter->key.code = sf::Keyboard::Num1;
		eventIter++;
		eventIter->type = sf::Event::KeyPressed;
		eventIter->key.code = sf::Keyboard::Escape;
		eventIter++;
		eventIter->type = sf::Event::KeyPressed;
		eventIter->key.code = sf::Keyboard::Escape;
		eventIter++;
		eventIter->type = sf::Event::KeyPressed;
		eventIter->key.code = sf::Keyboard::A;
		eventIter++;
		eventIter++;
		eventIter->type = sf::Event::MouseButtonPressed;
		eventIter->mouseButton = { sf::Mouse::Left, 50, 50};
		eventIter++;
		eventIter->type = sf::Event::MouseButtonPressed;
		eventIter->mouseButton = { sf::Mouse::Left, 1850, 50 };
		eventIter++;


		appData.loadAssets();
		controller.load();

		for (size_t idx = 0; controller.isActive(); idx++) {
			if (idx == events.size()) {
				std::string message;
				message += "Simulation reached end of control.";
				throw std::range_error{ message };
			}
			if (events[idx].type == sf::Event::KeyPressed && events[idx].key.code == sf::Keyboard::F4 && events[idx].key.alt) {
				break;
			}
			controller->handleEvent(events[idx]);
			controller->update();
		}
        window.cleanUp();
		appData.save();
        appData.cleanUp();


		std::cout << "Success!\n";
	}
	catch (const std::exception& e) {
		std::cout << "Failure!\n";
		std::cout << "Message:\t" << e.what() << '\n';
	}
	std::cout << "\n\n";
}


int main() {
	write_title();

	// Unit tests
	test_class<util::vector<int>>();
	test_class<PlayerSprite>();
	test_class<Player>();
	test_class<ContextManager>();
	test_class<MenuNode>();
	test_class<Controller>();

	// Integrity tests
	run_comprehensive_test_1();
	run_comprehensive_test_2();

	// Simulations
	simulation_1();

	return 0;
}

#endif // CPORTA
