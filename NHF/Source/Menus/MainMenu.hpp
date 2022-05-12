#pragma once

#include "Menu.hpp"
#include "GameMenu/Track.hpp"
#include "GameMenu/Player.hpp"


class TrackAI : public Track {
public:
	void handleEvent(const sf::Event&) override { /* AI only */ }
};
class PlayerAI : public Player {
public:
	void jump() {
		startJump();
	}
	void handleEvent(const sf::Event&) override { /* AI only */ }
};
class Shader : public MenuItem {
	sf::RectangleShape _item{ Window::getSize() };
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_item); }
public:
	Shader() {
		_item.setFillColor({ 0, 0, 0, 220 });
	}
};


class MainMenu : public Menu {
private:
	// Background
	TrackAI* _track;
	PlayerAI* _player;

public:
	MainMenu();

	void handleEvent(const sf::Event& event) override;
	void update() override;
};
