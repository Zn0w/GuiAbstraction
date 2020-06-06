#pragma once

#include "../component.h"


class Label : public Component
{
protected:
	sf::Text text;


public:
	Label() {}

	Label(Position p) : Component(p) {}

	Label(sf::Text s_text)
	{
		setText(s_text);
	}

	void setText(sf::Text s_text)
	{
		text = s_text;
		text.setPosition(position.x, position.y);
		sf::FloatRect rect = text.getLocalBounds();
		position.width = rect.width;
		position.height = rect.height;
	}

	sf::Text getText() { return text; }

	void render(sf::RenderWindow* window)
	{
		text.setPosition(position.x, position.y);

		window->draw(text);
	}
};