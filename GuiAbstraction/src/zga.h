#pragma once

#include <vector>
#include <string>


struct Position
{
	int x, y, width, height;
};

class Component
{
protected:
	Position position;


public:
	virtual void render(sf::RenderWindow* window) = 0;
	
	Component() {}
	Component(Position p) { setPosition(p); }

	void setPosition(Position p) { position = p; }
	Position getPosition() { return position; }
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
			component->render(window);
	}
};

// Containers implementations ...

class Label : public Component
{
protected:
	sf::Text text;


public:
	Label() {}
	Label(Position p) : Component(p) {}
	Label(sf::Text stext) { setText(stext); }

	void setText(sf::Text stext) { text = stext; }
	sf::Text getText() { return text; }

	void render(sf::RenderWindow* window)
	{
		text.setPosition(position.x, position.y);
		window->draw(text);
	}
};

class Button : public Label
{
protected:
	void(*handle_action) () = 0;

	sf::Color fill_color = sf::Color(230, 230, 230, 255);
	sf::Color outline_color = sf::Color(230, 230, 230, 255);

	bool clicked = false;


public:
	Button() {}
	Button(Position p) : Label(p) {}
	Button(sf::Text stext) : Label(stext) {}
	Button(sf::Text stext, sf::Color sfill_color, sf::Color soutline_color) : Label(stext)
	{
		setFillColor(sfill_color);
		setOutlineColor(soutline_color);
	}
	Button(sf::Color sfill_color, sf::Color soutline_color) {}

	void setHandleAction(void(*shandle_action)()) { handle_action = shandle_action; }

	void setFillColor(sf::Color sfill_color) { fill_color = sfill_color; }
	sf::Color getFillColor() { return fill_color; }

	void setOutlineColor(sf::Color soutline_color) { outline_color = soutline_color; }
	sf::Color getOutlineColor() { return outline_color; }

	void render(sf::RenderWindow* window)
	{
		sf::RectangleShape shape;
		if (position.width == 0 && position.height == 0)
		{
			sf::FloatRect rect = text.getGlobalBounds();
			shape.setSize(sf::Vector2f(rect.width * 1.3f, rect.height * 2.0f));
		}
		else
			shape.setSize(sf::Vector2f(position.width, position.height));
		
		shape.setFillColor(fill_color);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(outline_color);
		shape.setPosition(position.x, position.y);
		text.setPosition(position.x, position.y);
		window->draw(shape);
		window->draw(text);

		// check if the button is clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
			sf::Vector2f button_pos = shape.getPosition();
			sf::Vector2f button_size = shape.getPosition();
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