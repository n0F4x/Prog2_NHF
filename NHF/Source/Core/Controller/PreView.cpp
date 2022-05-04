#include "PreView.hpp"

#include "../AppData.hpp"
#include "../Window.hpp"
#include "../../GUI/Widgets/Text.hpp"
#include "../../GUI/Theme.hpp"


void PreView::render() {
	// Construct title
	auto title = Text{ "PLATFORMS", AppData::getFont("The Wireframe"), 186u };
	title.center(Window::getLocalBounds());
	title.setFillColor(theme::Secondary);

	Window::clear();
	Window::draw(title);
	Window::display();
}
