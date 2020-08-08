#pragma once
#include "draw_area.h"
/// Class for managing the different Colours
/// Creates buttons for each
class ColourPalette
{
public:
	/// array of colours
	static const Colour colours[];
	/// colour selected by user
	static int selectedIndex;
	/// x position of colour box
	static int palette_x_pos;
	/// Draws the colour palette on screen
	static void Display(int window_width, int window_height)
	{
		palette_x_pos = window_width - 50;
		glBegin(GL_QUADS);		// draws buttons for each colour
		int xPos = palette_x_pos;
		int yPos = 50;
		for (int i = 0; i < 10; i++)
		{
			glColor3f(1.0f,1.0f, 1.0f);
			glVertex2f(xPos, window_height - yPos);
			glVertex2f(xPos + 50, window_height - yPos);
			glVertex2f(xPos + 50, window_height - (yPos + 50));
			glVertex2f(xPos, window_height - (yPos + 50));
			glColor3f(colours[i].r, colours[i].g, colours[i].b);
			glVertex2f(xPos + 2, window_height - (yPos + 2));
			glVertex2f(xPos + 46, window_height - (yPos + 2));
			glVertex2f(xPos + 46, window_height - (yPos + 46));
			glVertex2f(xPos + 2, window_height - (yPos + 46));
			yPos += 49;
		}
		glEnd();
	}
	/// Checks if (x,y) coordinate is within a given rect
	static bool checkInside(int x, int y, int x_pos, int y_pos, int width, int height)
	{
		if (x >= x_pos)
		{
			if (y >= y_pos)
			{
				if (x < x_pos + width)
				{
					if (y < y_pos + height)
						return true;
				}
			}
		}
		return false;
	}
	/// Checks if the mouse was pressed upon a colour
	static bool Pressed(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				int xPos = palette_x_pos;
				int yPos = 50;
				for (int i = 0; i < 10; i++)
				{
					if (checkInside(x, y, xPos, yPos, 50, 50))
					{
						selectedIndex = i;
						selectedColour = colours[i];
						return true;
					}
					yPos += 49;
				}
			}
		}
		return checkInside(x, y, palette_x_pos, 50, 50, 490);
	}
};