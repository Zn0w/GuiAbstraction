#pragma once

namespace zn {

	class Element
	{
	protected:
		int x, y, width, height;
		const char* contents;		// To be displayed

	public:
		inline int getX() { return x; }
		inline int getY() { return y; }
		inline int getWidth() { return width; }
		inline int getHeight() { return height; }

		inline void setX(int s_x) { x = s_x; }
		inline void setY(int s_y) { y = s_y; }
		inline void setWidth(int s_width) { width = s_width; }
		inline void setHeight(int s_height) { height = s_height; }

		inline void setContents(const char* c) { contents = c; }
		inline const char* getContents() { return contents; }

		Element(const char* c)
			: x(0), y(0), width(20), height(15), contents(c)
		{}

		Element(const char* c, int w, int h)
			: x(0), y(0), width(w), height(h), contents(c)
		{}

		Element(const char* c, int s_x, int s_y, int w, int h)
			: x(s_x), y(s_y), width(w), height(h), contents(c)
		{}
	};

	class Button : public Element
	{
	private:
		void(*action) ();

	public:
		Button(const char* c)
			: Element(c)
		{}

		Button(const char* c, int w, int h)
			: Element(c, w, h)
		{}

		Button(const char* c, int s_x, int s_y, int w, int h)
			: Element(c, s_x, s_y, w, h)
		{}

		inline void setAction(void(*a) ()) { action = a; }
	};

}