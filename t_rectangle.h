#pragma once
/// Responsible for mouse input
///
/// Checks if pointer is pressed/released/inside canvas/outside canvas
/// gets mouse coordinates
/// Calls appropriate function
bool Tool_Rect::Pressed(int button, int state, int x, int y)
{
	if (currentCanvas.checkInside(x, y))
	{
		// relates mouse position to canvas position
		int cx = (x - currentCanvas.xOffset);
		int cy = (y - currentCanvas.yOffset);
		// stores start of drag coordinates
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && !isMouseDown)
		{
			isMouseDown = true;
			startMouseX = cx;
			startMouseY = cy;
			return true;
		}
		// start drawing rectangle after key released
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP) && isMouseDown)
		{
			// calculating the rectangle coordinates
			int minX = std::min(cx, startMouseX);
			int maxX = std::max(cx, startMouseX);
			int minY = std::min(cy, startMouseY);
			int maxY = std::max(cy, startMouseY);
			// 2 horizontal lines
			for (int px = minX; px <= maxX; px++)
			{
				currentCanvas.SetPixelColour(px, minY, selectedColour);
				currentCanvas.SetPixelColour(px, maxY, selectedColour);
			}
			// 2 vertical lines
			for (int py = minY; py <= maxY; py++)
			{
				currentCanvas.SetPixelColour(minX, py, selectedColour);
				currentCanvas.SetPixelColour(maxX, py, selectedColour);
			}
		}
		isMouseDown = false;
		return true;
	}
	return false;
}