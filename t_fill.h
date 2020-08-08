#pragma once
#include <vector>
/// struct to store x,y pair
struct Tuple
{
	int x;
	int y;
};
Colour InteriorColour;
/// checks if agenda list if empty or not
bool agenda_empty = true;
/// An array to store x value of imaginary Boundaries
int ImgBoundaryX[200];
/// An array to store y value of imaginary Boundaries
int ImgBoundaryY[200];
/// m tracks the x values of ImgBoundaryX[]
int m = -1;
/// n tracks the y values of ImgBoundaryY[]
int n = -1;
/// This variable tracks scan Direction; True->UP, False->DOWN
bool Vdir = true;
/// Checks if S turn or U turn
bool turnType;
/// Horzontal Shade Direction is Left or Right
bool isLeft = true;
/// This function deals with S turns and U turns
///
/// IF turnType is true -> S Turn
/// False -> U Turn
void CheckTurns(bool turnType, int x, int y)
{
	if (turnType) //S Turn
	{
		m++;
		n++;
		ImgBoundaryX[m] = x;
		ImgBoundaryY[n] = y;
	}
	else //U Turn
	{
		m--;
		n--;
	}
}
/// This function shades vertically based on Vdir
///
/// Starts from x,y
/// Ends when reaches Imaginary Boundary or
/// Actual boundary
void ShadeVertically(bool Vdir, int x, int y, Colour C)
{
	Colour K = currentCanvas.GetPixelColour(x, y);
	while (K.r != C.r && K.g != C.g && K.b != C.b)
	{
		K.r = C.r;
		K.g = C.g;
		K.b = C.b;
		CheckTurns(turnType, x, y);
	}
}
/// Shades Horizontally
///
/// Ends when reaches Imaginary Boundary or
/// Actual boundary
void ShadeHorizontally(int x, int y, Colour C)
{
	Colour K = currentCanvas.GetPixelColour(x, y);
	while (K.r != C.r && K.g != C.g && K.b != C.b)
	{
		if (isLeft)
		{
			ShadeHorizontally(--x, y, C);
		}
		else
		{
			ShadeHorizontally(++x, y, C);
		}
	}
}
/// Scans in a particular direction
void scan(int x, int y, bool dir)
{
	if (dir)
		scan(x, --y, true);
	else
		scan(x, ++y, false);
}
/// Checks the vertical Direction and Starts Scanning
void agenda(int x, int y, Colour c)
{
	while (!agenda_empty)
		if (Vdir)
		{
			scan(x, y, true);
			Vdir = false;
		}
		else
		{
			scan(x, y, false);
		}
}
/// Given interior point x,y, fills it with color c
void Shade(int x, int y, Colour C)
{
	InteriorColour = C;
	Vdir = true;
	agenda(x, y, C);
	ShadeVertically(true, x, y, C);
	ShadeVertically(false, x, y, C);
}
/// for filling colour in an area
///
/// startColour holds the colour to be replaced
/// cx,cy are the coordinates of the point where fill tool was used
void Tool_Fill::Fill(Colour startColour, int cx, int cy)
{
	std::vector<Tuple> vec;
	std::vector<Tuple> newvec;
	Tuple startCoord = {cx, cy};
	vec.push_back(startCoord);
	while (vec.size() > 0)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			Colour colourAtPixel = currentCanvas.GetPixelColour(vec[i].x, vec[i].y);
			if ((colourAtPixel.r == startColour.r) && (colourAtPixel.g == startColour.g) && (colourAtPixel.b == startColour.b))
			{
				currentCanvas.SetPixelColour(vec[i].x, vec[i].y, selectedColour);
				if (vec[i].x < currentCanvas.width - 1)
				{
					Tuple newCoord = {vec[i].x + 1, vec[i].y};
					newvec.push_back(newCoord);
				}
				if (vec[i].x > 0)
				{
					Tuple newCoord = {vec[i].x - 1, vec[i].y};
					newvec.push_back(newCoord);
				}
				if (vec[i].y < currentCanvas.height - 1)
				{
					Tuple newCoord = {vec[i].x, vec[i].y + 1};
					newvec.push_back(newCoord);
				}
				if (vec[i].y > 0)
				{
					Tuple newCoord = {vec[i].x, vec[i].y - 1};
					newvec.push_back(newCoord);
				}
			}
		}
		vec.empty();
		vec = newvec;
		std::vector<Tuple> b;
		newvec = b;
	}
}
/// Handles mouse click when fill tool has already been selected
bool Tool_Fill::Pressed(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		int canvasCoordX = (x - currentCanvas.xOffset);
		int canvasCoordY = (y - currentCanvas.yOffset);
		Colour colourWherePressed = currentCanvas.GetPixelColour(canvasCoordX, canvasCoordY);
		if ((colourWherePressed.r != selectedColour.r) || (colourWherePressed.g != selectedColour.g) || (colourWherePressed.b != selectedColour.b))
		{
			Tool_Fill::Fill(colourWherePressed, canvasCoordX, canvasCoordY);
			return true;
		}
	}
	return false;
}