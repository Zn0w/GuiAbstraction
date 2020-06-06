#pragma once

#include "component.h"


class Container : public Component
{
protected:
	std::vector<Component*> components;


protected:
	virtual void align() = 0;
public:
	void add(Component* component)
	{
		components.push_back(component);
	}

	int get_index(Component* component)
	{
		std::vector<Component*>::iterator it = std::find(components.begin(), components.end(), component);
		int index = std::distance(components.begin(), it);
		return index;
	}

	void remove(Component* component)
	{
		int index = get_index(component);
		components.erase(components.begin() + index);
	}

	void remove(int index)
	{
		components.erase(components.begin() + index);
	}

	void setComponents(std::vector<Component*> s_components)
	{
		components = s_components;
	}

	std::vector<Component*> getComponents() { return components; }
};