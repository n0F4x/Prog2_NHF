#include "App.hpp"

#include <iostream>
#include "vector.hpp"


void test_1() {
	std::cout << "TEST_1 - Create and run app\n";

	App app;
	app.run();

	std::cout << "Success!\n";
}

void test_2() {
	std::cout << "TEST_2 - Start game\n";

	App app;
	app.run();

	util::vector<sf::Event> events;
	events.emplace_back(sf::Event::KeyPressed, sf::Event::KeyEvent{ sf::Keyboard::Num1 });
	events.emplace_back(sf::Event::Closed);

	for (auto it = events.begin(); it != events.end() && app.isRunning(); it++) {
		app.handleEvent(*it);
	}

	std::cout << "Success!\n";
}


int main() {
	try {
		int nr;
		std::cin >> nr;
		switch (nr) {
		case 1:
			test_1();
			break;

		case 2:
			test_2();
			break;

		default:
			std::cout << "Invalid test number\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "*** Nagy baj van! ***" << std::endl;
	}

	return 0;
}
