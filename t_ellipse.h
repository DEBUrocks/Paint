#pragma once
/// Responsible for mouse input
///
/// Checks if pointer is pressed/released/inside canvas/outside canvas
/// gets mouse coordinates
/// Calls appropriate function
bool Tool_Circ::Pressed(int button, int state, int x, int y)
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
		// start drawing circle after key released
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP) && isMouseDown)
		{
			// get the rect coordinates to put the circle in
			int minX = std::min(cx, startMouseX);
			int maxX = std::max(cx, startMouseX);
			int minY = std::min(cy, startMouseY);
			int maxY = std::max(cy, startMouseY);
			// work out the radii and center coords
			float radH = (maxX - minX) / 2;
			float radV = (maxY - minY) / 2;
			float centX = (maxX + minX) / 2;
			float centY = (maxY + minY) / 2;
			for (int px = 0; px <= maxX - minX; px++)
			{
				for (int py = 0; py <= maxY - minY; py++)
				{
					if ((std::pow(((px + minX) - centX) / radH, 2) + std::pow(((py + minY) - centY) / radV, 2)) < 1)
						currentCanvas.SetPixelColour(minX + px, minY + py, selectedColour);
				}
			}
			isMouseDown = false;
			return true;
		}
	}
	return false;
}