#pragma once

#include "button.h"


class GameMenuItem : public Button
{
protected:
	sf::Color selected_fill_color = sf::Color(255, 255, 255, 200);
	sf::Color selected_outline_color = sf::Color(255, 255, 255, 230);
	sf::Color selected_text_color = sf::Color(0, 0, 0, 255);
	sf::Color text_color = sf::Color(0, 0, 0, 255);

	bool selected = false;

public:
	GameMenuItem() {}

	GameMenuItem(Position p) : Button(p) {}

	GameMenuItem(sf::Text s_text) : Button(s_text) {}

	GameMenuItem(sf::Text s_text, sf::Color s_fill_color, sf::Color s_outline_color) : Button(s_text, s_fill_color, s_outline_color) {}

	GameMenuItem(sf::Color s_fill_color, sf::Color s_outline_color) : Button(s_fill_color, s_outline_color) {}

	GameMenuItem(
		sf::Color s_fill_color,
		sf::Color s_outline_color,
		sf::Color selected_fill_color,
		sf::Color s_selected_fill_color,
		sf::Color s_selected_outline_color,
		sf::Color s_selected_text_color
	) : Button(s_fill_color, s_outline_color)
	{
		setSelectedFillColor(s_selected_fill_color);
		setSelectedOutlineColor(s_selected_outline_color);
		setSelectedTextColor(s_selected_text_color);
	}

	GameMenuItem(
		sf::Text s_text,
		sf::Color s_fill_color,
		sf::Color s_outline_color,
		sf::Color selected_fill_color,
		sf::Color s_selected_fill_color,
		sf::Color s_selected_outline_color,
		sf::Color s_selected_text_color
	) : Button(s_text, s_fill_color, s_outline_color)
	{
		setSelectedFillColor(s_selected_fill_color);
		setSelectedOutlineColor(s_selected_outline_color);
		setSelectedTextColor(s_selected_text_color);
	}

	void setSelectedFillColor(sf::Color s_selected_fill_color)
	{
		selected_fill_color = s_selected_fill_color;
	}

	void setSelectedOutlineColor(sf::Color s_selected_outline_color)
	{
		selected_outline_color = s_selected_outline_color;
	}

	void setSelectedTextColor(sf::Color s_selected_text_color)
	{
		selected_text_color = s_selected_text_color;
	}

	sf::Color getSelectedFillColor() { return selected_fill_color; }

	sf::Color getSelectedOutlineColor() { return selected_outline_color; }

	sf::Color getSelectedTextColor() { return selected_text_color; }

	void setSelected(bool value)
	{
		selected = value;
	}

	bool isSelected() { return selected; }

	void render(sf::RenderWindow* window)
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
		sf::Vector2f menu_item_pos = sf::Vector2f(position.x, position.y);
		sf::Vector2f menu_item_size = sf::Vector2f(position.width, position.height);
		// check if the mouse cursor is hovered over the menu item
		if (
			mouse_pos.x <= menu_item_pos.x + menu_item_size.x &&
			mouse_pos.x >= menu_item_pos.x &&
			mouse_pos.y <= menu_item_pos.y + menu_item_size.y &&
			mouse_pos.y >= menu_item_pos.y
			)
		{
			selected = true;
		}
		else
		{
			selected = false;
		}
		
		if (selected)
		{
			shape.setFillColor(selected_fill_color);
			shape.setOutlineThickness(2);
			shape.setOutlineColor(selected_outline_color);
			shape.setPosition(position.x, position.y);
			shape.setSize(sf::Vector2f(position.width, position.height));
			text.setPosition(position.x, position.y);
			
			text_color = text.getFillColor();
			text.setFillColor(selected_text_color);
		}
		else
		{
			shape.setFillColor(fill_color);
			shape.setOutlineThickness(2);
			shape.setOutlineColor(outline_color);
			shape.setPosition(position.x, position.y);
			shape.setSize(sf::Vector2f(position.width, position.height));
			text.setPosition(position.x, position.y);

			text.setFillColor(text_color);
		}

		window->draw(shape);
		window->draw(text);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selected)
		{
			clicked = true;
		}
		else if (clicked)
		{
			if (handle_action)
				handle_action();
			clicked = false;
		}
	}
};