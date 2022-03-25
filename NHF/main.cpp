#include <cstdlib>
#include <ctime>
#include "App.hpp"


int main() {
	App app;
	srand(time(NULL));

	app.run();

	return 0;
}