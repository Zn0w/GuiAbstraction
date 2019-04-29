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
	};

}