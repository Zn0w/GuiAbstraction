#pragma once

#include "../component.h"


class Button : public Component
{
protected:
	std::function<void()> handle_action = 0;

	sf::Color fill_color = sf::Color(230, 230, 230, 255);
	sf::Color outline_color = sf::Color(230, 230, 230, 255);

	bool clicked = false;

	sf::RectangleShape shape;
	sf::Text text;


public:
	Button() {}

	Button(Position p) : Component(p) {}

	Button(sf::Text s_text)
	{
		setText(s_text);
	}

	Button(sf::Text s_text, sf::Color s_fill_color, sf::Color s_outline_color)
	{
		setText(s_text);
		setFillColor(s_fill_color);
		setOutlineColor(s_outline_color);
	}

	Button(sf::Color s_fill_color, sf::Color s_outline_color)
	{
		setFillColor(s_fill_color);
		setOutlineColor(s_outline_color);
	}

	void setText(sf::Text s_text)
	{
		text = s_text;
		sf::FloatRect rect = text.getGlobalBounds();
		position.width = rect.width * 1.3f;
		position.height = rect.height * 2.0f;
	}

	sf::Text getText() { return text; }

	void setHandleAction(std::function<void()> s_handle_action) { handle_action = s_handle_action; }

	void setFillColor(sf::Color s_fill_color)
	{
		fill_color = s_fill_color;
	}

	sf::Color getFillColor() { return fill_color; }

	void setOutlineColor(sf::Color s_outline_color)
	{
		outline_color = s_outline_color;
	}

	sf::Color getOutlineColor() { return outline_color; }

	void render(sf::RenderWindow* window)
	{
		shape.setFillColor(fill_color);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(outline_color);
		shape.setPosition(position.x, position.y);
		shape.setSize(sf::Vector2f(position.width, position.height));
		text.setPosition(position.x, position.y);

		window->draw(shape);
		window->draw(text);

		// check if the button is clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
			sf::Vector2f button_pos = sf::Vector2f(position.x, position.y);
			sf::Vector2f button_size = sf::Vector2f(position.width, position.height);
			if (
				mouse_pos.x <= button_pos.x + button_size.x &&
				mouse_pos.x >= button_pos.x &&
				mouse_pos.y <= button_pos.y + button_size.y &&
				mouse_pos.y >= button_pos.y
				)
			{
				clicked = true;
			}
		}
		else if (clicked)
		{
			if (handle_action)
				handle_action();
			clicked = false;
		}
	}
};