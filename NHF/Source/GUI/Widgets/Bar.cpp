#include "Bar.hpp"

#include "../Theme.hpp"


template class Bar<bool>;
template class Bar<int>;
template class Bar<PlatformControl>;


template<typename T>
void Bar<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& text : _texts)
		target.draw(text);

	target.draw(_emphasis);

	for (const auto& cell : _cells)
		target.draw(cell);
}


template<typename T>
Bar<T>::Bar(
	float width,
	const std::vector<T>& contents,
	const sf::Font& font,
	unsigned chararcterSize,
	const std::string_view& contextName
) :
	_context{ AppData::findContext(contextName) },
	_contents{ contents }
{
	sf::Vector2f cellSize = { width / static_cast<float>(_contents.size()), Text{ "0", font, chararcterSize }.getSize().y * 2.f };

	_cells.resize(contents.size());
	for (size_t i = 0; i < _cells.size(); i++) {
		_cells[i].setSize(cellSize);
		_cells[i].move({ cellSize.x * static_cast<float>(i), 0.f });
		_cells[i].setFillColor(sf::Color::Transparent);
		_cells[i].setOutlineColor(theme::IndigoPurple);
		_cells[i].setOutlineThickness(2.f);
	}

	_texts.resize(contents.size());
	for (size_t i = 0; i < _texts.size(); i++) {
		_texts[i] = Text{ _context.string(contents[i]), font, chararcterSize };
		_texts[i].center(_cells[i].getLocalBounds());
		_texts[i].move(_cells[i].getPosition());
		_texts[i].setFillColor(theme::IndigoPurple);
	}

	_emphasis.setSize(cellSize);
	_emphasis.setPosition(_cells[_selected].getPosition());
	_emphasis.setFillColor(theme::Tertiary);

	setSize({ cellSize.x * static_cast<float>(_contents.size()), cellSize.y });

	addTransition(&_transition);
}


template<typename T>
void Bar<T>::setPosition(const sf::Vector2f& position) {
	for (sf::RectangleShape& cell : _cells) {
		cell.setPosition(position + (cell.getPosition() - getPosition()));
	}
	for (Text& content : _texts) {
		content.setPosition(position + (content.getPosition() - getPosition()));
	}

	_emphasis.setPosition(position + (_emphasis.getPosition() - getPosition()));

	Widget::setPosition(position);
}


template<typename T>
void Bar<T>::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		for (size_t i = 0; i < _cells.size(); i++) {
			if (_cells[i].getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition(Window::window()) })) {
				_context = _contents[i];
				_selected = i;
			}
		}
	}
}

template<typename T>
void Bar<T>::update() {
	if (_context != _contents[_activeCell] && !_transition.isActive()) {
		_transition.start(_cells[_selected].getPosition() - _emphasis.getPosition(), 200);
		_activeCell = _selected;
	}

	MenuItem::update();
}

template<typename T>
void Bar<T>::init() {
	MenuItem::init();

	_context.update();
	for (size_t i = 0; i < _texts.size(); i++) {
		if (_contents[i] == _context) {
			_emphasis.setPosition(_cells[i].getPosition());
			_selected = i;
			_activeCell = i;
		}
	}
}
