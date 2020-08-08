#include <iostream>
#include <vector>
#include <cstring>
/// Used to write text over a button
void draw_text(std::string text)
{
	size_t len = text.size();
	for (size_t i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
}
/// Controls the size and position of text before calling draw_text()
void display_text(std::string text, float x, float y)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f); 
	glTranslatef(x, y, 0.0f);
	glScalef(0.22f, 0.22f, 1.0f);
	draw_text(text);
	glPopMatrix();
}
class Button;
/// a Callback issued when button clicked
typedef void (*Callback)(Button button);
/// Class for Button functionality
class Button
{
public:
	/// callback function when button pressed
	Button() : callback(NULL) {}
	/// callback
	Callback callback;
	/// pointer above a button or not
	bool hovering;
	/// x position of button
	int x_pos;
	/// y position of button
	int y_pos;
	/// width of button
	int width;
	/// height of button
	int height;
	/// The name of the button
	std::string text;
	/// x,y is inside a button or not
	bool checkInside(int x, int y)
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
	/// true if x,y is inside a button
	bool Hover(int x, int y)
	{
		hovering = checkInside(x, y);
		return hovering;
	}
	/// Handles mouse input, Mouse location and click
	bool Pressed(int button, int state, int x, int y)
	{
		hovering = checkInside(x, y);
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				if (hovering)
				{
					if (callback)
						(*callback)((Button) * this);
					return true;
				}
			}
		}
		return hovering;
	}
	/// Displays the button on screen
	void Display(int window_width, int window_height)
	{
		glBegin(GL_QUADS);
		glColor3f(0.5f, 0.1f, 0.2f);
		glVertex2f(x_pos + 2, window_height - y_pos - 2);
		glVertex2f(x_pos + width - 2, window_height - y_pos - 2);
		glVertex2f(x_pos + width - 2, window_height - y_pos - height + 2);
		glVertex2f(x_pos + 2, window_height - y_pos - height + 2);
		glEnd();
		display_text(text, x_pos + 7, window_height - y_pos - height + 10);
	}
	/// Sets all the values of a button
	///
	/// Position and Size of button
	/// width and height of a button
	/// name of butotn
	/// which function to callback when clicked
	void set_values(int x, int y, int w, int h, char *t, Callback c)
	{
		hovering = false;
		x_pos = x;
		y_pos = y;
		width = w;
		height = h;
		text = t;
		callback = c;
	}
	/// Creates a button with given values
	static Button Create(int x, int y, int w, int h, char *t, Callback c)
	{
		Button *newButton = new Button;
		newButton->set_values(x, y, w, h, t, c);
		return *newButton;
	}
};
