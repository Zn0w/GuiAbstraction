#pragma once

#include "container.h"


class Gui
{
protected:
	Container * root;


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