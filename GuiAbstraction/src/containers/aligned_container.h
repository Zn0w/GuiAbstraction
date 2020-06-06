#pragma once

#include "../container.h"


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