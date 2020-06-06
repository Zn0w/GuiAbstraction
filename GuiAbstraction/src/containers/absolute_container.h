#pragma once

#include "../container.h"


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