#pragma once
/// Responsible for mouse input
///
/// Checks if pointer is pressed/released/inside canvas/outside canvas
/// gets mouse coordinates
/// Calls appropriate function
bool Tool_Pen::Pressed(int button, int state, int x, int y)
{
	if (currentCanvas.checkInside(x, y))
	{
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && !isMouseDown)
		{
			isMouseDown = true;
			mouseLastX = (x - currentCanvas.xOffset);
			mouseLastY = (y - currentCanvas.yOffset);
			return true;
		}
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP) && isMouseDown)
		{
			isMouseDown = false;
			return true;
		}
	}
	return false;
}
/// True if pencil tool is already selected
///
/// If true then hover x,y will provide the  coordinates where we have to draw
bool Tool_Pen::Hover(int x, int y)
{
	if (isMouseDown)
	{
		if (currentCanvas.checkInside(x, y))
		{	// relate mouse position to canvas coordinates
			int canvasCoordX = (x - currentCanvas.xOffset);
			int canvasCoordY = (y - currentCanvas.yOffset);
			int minX = std::min(canvasCoordX, mouseLastX);
			int maxX = std::max(canvasCoordX, mouseLastX);
			int minY = std::min(canvasCoordY, mouseLastY);
			int maxY = std::max(canvasCoordY, mouseLastY);
			double length = std::sqrt(std::pow(maxX - minX, 2) + std::pow(maxY - minY, 2));// unit vector-> last mouse pos to current mouse pos
			double moveX = (canvasCoordX - mouseLastX) / length;
			double moveY = (canvasCoordY - mouseLastY) / length;
			double curX = mouseLastX;
			double curY = mouseLastY;
			while ((curX <= maxX) && (curY <= maxY) && (curX >= minX) && (curY >= minY))
			{
				currentCanvas.SetPixelColour(round(curX), round(curY), selectedColour);
				curX += moveX;
				curY += moveY;
			}
			mouseLastX = canvasCoordX;
			mouseLastY = canvasCoordY;
		}
		return true;
	}
	return currentCanvas.checkInside(x, y);
}