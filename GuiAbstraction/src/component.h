#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>

#include <SFML/Graphics.hpp>


struct Position
{
	int x = 0, y = 0, width = 0, height = 0;
};

class Component
{
protected:
	Position position;
	bool visible = true;


public:
	virtual void render(sf::RenderWindow* window) = 0;

	Component() {}
	Component(Position p) { setPosition(p); }

	void setPosition(Position s_position) { position = s_position; }
	Position getPosition() { return position; }

	void setVisible(bool value) { visible = value; }
	bool isVisible() { return visible; }
};