#pragma once

#include <vector>
#include <string>
#include <functional>

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

	void setPosition(Position p) { position = p; }
	Position getPosition() { return position; }

	void setVisible(bool value) { visible = value; }
	bool isVisible() { return visible; }
};

class Container : public Component
{
protected:
	std::vector<Component*> components;


protected:
	virtual void align() = 0;
public:
	void add(Component* component) { components.push_back(component); }
	//void remove(Component cpmponent) { components }

	// remove??
	//std::vector<Component*> getComponents() { return components; }
};

class AbsoluteContainer : public Container
{
protected:
	void align() {}

public:
	void render(sf::RenderWindow* window)
	{
		// no align
		for (Component* component : components)
			if (component->isVisible())
				component->render(window);
	}
};

enum HorizontalAlignMode
{
	LEFT, RIGHT, HORIZONTAL_CENTER, HORIZONTAL_CUSTOM
};

enum VerticalAlignMode
{
	TOP, BOTTOM, VERTICAL_CENTER, VERTICAL_CUSTOM
};

class AlignedContainer : public Container
{
protected:
	HorizontalAlignMode hor_align_mode;
	VerticalAlignMode vert_align_mode;
	int margin = 25;


public:
	AlignedContainer(HorizontalAlignMode s_hor_align_mode, VerticalAlignMode s_vert_align_mode, Position s_position)
		: hor_align_mode(s_hor_align_mode), vert_align_mode(s_vert_align_mode)
	{
		position = s_position;
	}

	void setMargin(int value) { margin = value; }
	int getMargin() { return margin; }
};

class VerticalContainer : public AlignedContainer
{
protected:
	void align()
	{
		int y = 0;
		if (hor_align_mode == LEFT)
		{
			for (Component* component : components)
			{
				Position new_position = component->getPosition();
				new_position.x = position.x;
				new_position.y = position.y + y;
				component->setPosition(new_position);
				y += new_position.height;
				y += margin;
			}
		}
		else if (hor_align_mode == RIGHT)
		{
			for (Component* component : components)
			{
				Position new_position = component->getPosition();
				new_position.x = position.x + position.width - new_position.width;
				new_position.y = position.y + y;
				component->setPosition(new_position);
				y += new_position.height;
				y += margin;
			}
		}
		else if (hor_align_mode == HORIZONTAL_CENTER)
		{
			for (Component* component : components)
			{
				Position new_position = component->getPosition();
				new_position.x = position.x + position.width / 2 - new_position.width / 2;
				new_position.y = position.y + y;
				component->setPosition(new_position);
				y += new_position.height;
				y += margin;
			}
		}

		// offset the y position according to the vertical align mode
		if (vert_align_mode == TOP)
		{
			// no changes needed
		}
		else if (vert_align_mode == BOTTOM)
		{
			Position last_element_position = components.back()->getPosition();
			int space_left_until_bottom = (position.y + position.height) - (last_element_position.y + last_element_position.height);
			if (space_left_until_bottom)
			{
				for (Component* component : components)
				{
					Position new_position = component->getPosition();
					new_position.y += space_left_until_bottom;
					component->setPosition(new_position);
				}
			}
		}
		else if (vert_align_mode == VERTICAL_CENTER)
		{
			Position last_element_position = components.back()->getPosition();
			int space_left_until_bottom = (position.y + position.height) - (last_element_position.y + last_element_position.height);
			int offset = space_left_until_bottom / 2;
			if (space_left_until_bottom)
			{
				for (Component* component : components)
				{
					Position new_position = component->getPosition();
					new_position.y += offset;
					component->setPosition(new_position);
				}
			}
		}
	}

public:
	VerticalContainer(HorizontalAlignMode s_hor_align_mode, VerticalAlignMode s_vert_align_mode, Position s_position) 
		: AlignedContainer(s_hor_align_mode, s_vert_align_mode, s_position)
	{}

	void render(sf::RenderWindow* window)
	{
		align();
		for (Component* component : components)
			if (component->isVisible())
				component->render(window);
	}
};

class HorizontalContainer : public AlignedContainer
{
protected:
	void align()
	{
		int x = 0;
		if (vert_align_mode == TOP)
		{
			for (Component* component : components)
			{
				Position new_position = component->getPosition();
				new_position.x = position.x + x;
				new_position.y = position.y;
				component->setPosition(new_position);
				x += new_position.width;
				x += margin;
			}
		}
		else if (vert_align_mode == BOTTOM)
		{
			for (Component* component : components)
			{
				Position new_position = component->getPosition();
				new_position.x = position.x + x;
				new_position.y = position.y + position.height - new_position.height;
				component->setPosition(new_position);
				x += new_position.width;
				x += margin;
			}
		}
		else if (vert_align_mode == VERTICAL_CENTER)
		{
			for (Component* component : components)
			{
				Position new_position = component->getPosition();
				new_position.x = position.x + x;
				new_position.y = position.y + position.height / 2 - new_position.height / 2;
				component->setPosition(new_position);
				x += new_position.width;
				x += margin;
			}
		}
		
		if (hor_align_mode == LEFT)
		{
			// no changes needed
		}
		else if (hor_align_mode == RIGHT)
		{
			Position last_element_position = components.back()->getPosition();
			int space_left_until_right = (position.x + position.width) - (last_element_position.x + last_element_position.width);
			if (space_left_until_right)
			{
				for (Component* component : components)
				{
					Position new_position = component->getPosition();
					new_position.x += space_left_until_right;
					component->setPosition(new_position);
				}
			}
		}
		else if (hor_align_mode == HORIZONTAL_CENTER)
		{
			Position last_element_position = components.back()->getPosition();
			int space_left_until_right = (position.x + position.width) - (last_element_position.x + last_element_position.width);
			int offset = space_left_until_right / 2;
			if (space_left_until_right)
			{
				for (Component* component : components)
				{
					Position new_position = component->getPosition();
					new_position.x += offset;
					component->setPosition(new_position);
				}
			}
		}
	}

public:
	HorizontalContainer(HorizontalAlignMode s_hor_align_mode, VerticalAlignMode s_vert_align_mode, Position s_position)
		: AlignedContainer(s_hor_align_mode, s_vert_align_mode, s_position)
	{}

	void render(sf::RenderWindow* window)
	{
		align();
		for (Component* component : components)
			if (component->isVisible())
				component->render(window);
	}
};


class Label : public Component
{
protected:
	sf::Text text;


public:
	Label() {}
	
	Label(Position p) : Component(p)
	{
		//text.setPosition(sf::Vector2f(position.x, position.y));
	}

	Label(sf::Text stext)
	{
		setText(stext);
	}

	void setText(sf::Text stext)
	{
		text = stext;
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
	Button()
	{
		shape.setFillColor(fill_color);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(outline_color);
	}
	
	Button(Position p) : Component(p)
	{
		/*shape.setFillColor(fill_color);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(outline_color);
		shape.setPosition(position.x, position.y);*/
	}

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
	Button(sf::Color sfill_color, sf::Color soutline_color) {}

	void setText(sf::Text s_text)
	{
		text = s_text;
		sf::FloatRect rect = text.getGlobalBounds();
		position.width = rect.width * 1.3f;
		position.height = rect.height * 2.0f;
	}

	sf::Text getText() { return text; }

	void setHandleAction(std::function<void()> shandle_action) { handle_action = shandle_action; }

	void setFillColor(sf::Color sfill_color)
	{
		fill_color = sfill_color;
	}

	sf::Color getFillColor() { return fill_color; }

	void setOutlineColor(sf::Color soutline_color)
	{
		outline_color = soutline_color;
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

// TODO : text field

class Gui
{
protected:
	Container* root;


public:
	Gui() {}
	Gui(Container* container) { root = container; }

	void setRoot(Container* container) { root = container; }
	Container* getRoot() { return root; }

	void display(sf::RenderWindow* window)
	{
		root->render(window);
	}
};