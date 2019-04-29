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

		virtual void allign(std::vector<Element> elements) = 0;
	};

	class AbsoluteLayout : public Layout
	{
	public:
		AbsoluteLayout()
		{
			marginX = 0;
			marginY = 0;
		}

		void allign(std::vector<Element> element)
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

	public:
		SequenceLayout(SequenceDirection d)
			: Layout()
		{
			direction = d;
		}

		SequenceLayout(SequenceDirection d, int m_x, int m_y)
			: Layout(m_x, m_y)
		{
			direction = d;
		}

		void allign(std::vector<Element> elements, int width, int height)
		{
			int next_position = 0;
			
			if (direction == X_AXIS)
			{	
				int rows = 0;
				int max_height;
				
				for (Element element : elements)
				{
					static int sum_width;

					sum_width += element.getWidth();
					
					if (width < sum_width)
					{
						rows++;
						sum_width = 0;
					}
				}
				
				for (Element element : elements)
				{
					element.setX(next_position);
					element.setY(height / 2);
				}
			}

			else if (direction == Y_AXIS)
			{

			}
		}
	};

}