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
};

// Containers implementations ...

class Label : public Component
{
protected:
	std::string text;


public:
	Label() {}
	Label(Position p) : Component(p) {}
	Label(std::string stext) { setText(stext); }
	Label(const char* stext) { setText(stext); }

	void setText(std::string stext) { text = stext; }
	void setText(const char* stext) { text = stext; }
};

class Button : public Label
{
protected:
	void(*handle_action) () = 0;


public:
	Button() {}
	Button(Position p) : Label(p) {}
	Button(std::string stext) : Label(stext) {}
	Button(const char* stext) : Label(stext) {}

	void setHandleAction(void(*shandle_action)()) { handle_action = shandle_action; }
};

// TODO : text field