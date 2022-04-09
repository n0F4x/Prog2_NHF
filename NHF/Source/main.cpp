#include <cstdlib>
#include <ctime>
#include "App.hpp"


int main() {
	srand(static_cast<unsigned>(time(NULL)));
	App app;

	app.run();

	return 0;
}