#pragma once
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
/// This canvas class has all properties for the Drawing Area
///
/// This class has the functions to enable the canvas for use
/// of drawing
class Canvas
{
public:
	/// Window width
	int width;
	/// Window height
	int height;
	/// Window width adjustment
	int xOffset;
	/// Window height adjustment
	int yOffset;
	/// 2D array of pixel colours
	Colour **pixels; 
	/// Sets the width, height and offsets for the Drawing area
	void set_values(int w, int h, int xo, int yo)
	{
		width = w;
		height = h;
		xOffset = xo;
		yOffset = yo;
		// fill in grid of pixels with white colour
		struct Colour white = {1.0f, 1.0f, 1.0f};
		pixels = new Colour *[w];
		for (int x = 0; x < w; ++x)
		{
			pixels[x] = new Colour[h * 5];
			for (int y = 0; y < h; y++)
				pixels[x][y] = white;
		}
	}
	/// Returns Pixel x,y Colour 
	Colour GetPixelColour(int x, int y)
	{
		return pixels[x][y];
	}
	/// sets Colour c for the given x,y coordinates
	void SetPixelColour(int x, int y, Colour c)
	{
		pixels[x][y] = c;
	}
	/// Draws a Quad, which represents a pixel
	void Draw(int window_width, int window_height)
	{
		glBegin(GL_QUADS);
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				glColor3f(pixels[x][y].r, pixels[x][y].g, pixels[x][y].b);
				glVertex2f(x + xOffset, window_height - (y + yOffset));
				glVertex2f((x + 1) + xOffset, window_height - (y + yOffset));
				glVertex2f((x + 1) + xOffset, window_height - ((y + 1) + yOffset));
				glVertex2f(x + xOffset, window_height - ((y + 1) + yOffset));
			}
		}
		glEnd();
	}
	/// True if point lies inside
	bool checkInside(int x, int y)
	{
		if (x >= xOffset)
		{
			if (y >= yOffset)
			{
				if (x < xOffset + (width))
				{
					if (y < yOffset + (height))
						return true;
				}
			}
		}
		return false;
	}
};
/// Draws the Canvas, the Drawing Area
Canvas NewCanvas(int w, int h, int xOffset, int yOffset)
{
	Canvas *newCanvas = new Canvas;
	newCanvas->set_values(w, h, xOffset, yOffset);
	return *newCanvas;
}
/// Declaring the Draw Area
static Canvas currentCanvas;
