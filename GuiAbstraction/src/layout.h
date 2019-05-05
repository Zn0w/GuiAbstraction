#pragma once

#include "frame.h"
#include "element.h"


namespace zn {

	class Layout
	{
	protected:
		int marginX, marginY;

	public:
		Layout()
		{
			marginX = 1;
			marginY = 1;
		}

		Layout(int m_x, int m_y)
		{
			marginX = m_x;
			marginY = m_y;
		}

		virtual void allign(std::vector<Element>* elements) = 0;

		inline void setMarginX(int m_x) { marginX = m_x; }
		inline void setMarginY(int m_y) { marginY = m_y; }
		inline int getMarginX() { return marginX; }
		inline int getMarginY() { return marginY; }
	};

	class AbsoluteLayout : public Layout
	{
	public:
		AbsoluteLayout()
		{
			marginX = 0;
			marginY = 0;
		}

		void allign(std::vector<Element>* element)
		{

		}
	};

	enum SequenceDirection
	{
		X_AXIS,
		Y_AXIS
	};

	class SequenceLayout : public Layout
	{
	private:
		SequenceDirection direction;
		int width, height;

	public:
		SequenceLayout(SequenceDirection d, int f_w, int f_h)
			: Layout()
		{
			direction = d;
			width = f_w;
			height = f_h;
		}

		SequenceLayout(SequenceDirection d, int f_w, int f_h, int m_x, int m_y)
			: Layout(m_x, m_y)
		{
			direction = d;
			width = f_w;
			height = f_h;
		}

		void allign(std::vector<Element>* elements) override
		{
			int next_position = marginX;
			
			if (direction == X_AXIS)
			{	
				int rows = 0;
				int max_height = 0;
				
				for (int i = 0; i < elements->size(); i++)
				{
					static int sum_width = marginX;

					sum_width += elements->at(i).getWidth() + marginX;
					
					if (width < sum_width)
					{
						rows++;
						sum_width = marginX;
						next_position = marginX;
					}

					if (max_height < elements->at(i).getHeight())
						max_height = elements->at(i).getHeight();

					elements->at(i).setX(next_position);
					elements->at(i).setY((height / 2) + (rows * (max_height + marginY)));

					next_position += elements->at(i).getWidth() + marginX;
				}
			}

			else if (direction == Y_AXIS)
			{

			}
		}

		inline void setFrameSize(int w, int h) { width = w; height = h; }
		inline int getFrameWidth() { return width; }
		inline int getFrameHeight() { return height; }
	};

}