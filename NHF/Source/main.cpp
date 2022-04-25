#include <cstdlib>
#include <ctime>
#include "App.hpp"


int main() {
	srand(static_cast<unsigned>(time(nullptr)));
	App app;

	app.run();

	return 0;
}
