#include "Window.hpp"


bool Window::_isOpen = false;


sf::Vector2f Window::getSize() {
	return sf::Vector2f{ 1920.f, 1080.f };
}

sf::FloatRect Window::getLocalBounds() {
	return sf::FloatRect{ 0.f, 0.f, getSize().x, getSize().y };
}


void Window::display() { /*Removed visuals*/ }

void Window::clear() { /*Removed visuals*/ }

void Window::draw(const sf::Drawable&, const sf::RenderStates&) { /*Removed visuals*/ }


void Window::open() const { _isOpen = true; /*Removed visuals*/ }

void Window::close() const { _isOpen = false; /*Removed visuals*/ }

bool Window::isOpen() const {
	return _isOpen;
}

bool Window::pollEvent(const sf::Event&) const { return false;/*Removed visuals*/ }
