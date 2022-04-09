#include "ButtonState.hpp"


ButtonState::ButtonState(size_t id, const sf::Color& color) : _color{ color }, State{ static_cast<size_t>(id) } {}
