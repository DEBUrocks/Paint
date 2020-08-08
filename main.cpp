#include <GL/glut.h>
#include <stddef.h>
#include <iostream>
#include <math.h>
#include "colours.h"
/// The initial colour will be Black
Colour selectedColour = {0.0f, 0.0f, 0.0f};
bool canvasAssigned = false;
#include "button.h"
int cursorX = 0;
int cursorY = 0;
#include "draw_area.h"
#include "colour_box.h"
const Colour ColourPalette::colours[] = 
{
	{0.0f, 0.0f, 0.0f}, // black
	{0.0f, 0.0f, 1.0f}, // blue
	{1.0f, 0.0f, 0.0f}, // red
	{1.0f, 1.0f, 0.0f}, // yellow
	{0.0f, 1.0f, 0.0f}, // green
	{1.0f, 0.5f, 0.0f}, // orange
	{1.0f, 0.5f, 1.0f}, // pink
	{0.7f, 0.0f, 1.0f}, // purple
	{0.5f, 0.3f, 0.3f}, // brown
	{1.0f, 1.0f, 1.0f}	// white
};
int ColourPalette::selectedIndex = 0;
int ColourPalette::palette_x_pos = 0;
#include "tools.h"
int Toolbar::selectedButton = 0;
Button Toolbar::penButton;
Button Toolbar::fillButton;
Button Toolbar::rectButton;
Button Toolbar::circleButton;
#include "t_pencil.h"
bool Tool_Pen::isMouseDown = false;
int Tool_Pen::mouseLastX = 0;
int Tool_Pen::mouseLastY = 0;
#include "t_fill.h"
#include "t_rectangle.h"
bool Tool_Rect::isMouseDown = false;
int Tool_Rect::startMouseX = 0;
int Tool_Rect::startMouseY = 0;
#include "t_ellipse.h"
bool Tool_Circ::isMouseDown = false;
int Tool_Circ::startMouseX = 0;
int Tool_Circ::startMouseY = 0;
/// The main display function
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	currentCanvas.Draw(720, 720);
	ColourPalette::Display(720, 720);
	Toolbar::Display(720, 720);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glutSwapBuffers();
}
/// Takes action if mouse is pressed
void mouse_click(int button, int state, int x, int y)
{	// if a tool is selected, mouse gives command to tool, otherwise commands the interface
	if (Toolbar::Pressed(button, state, x, y))
		return;
	if (ColourPalette::Pressed(button, state, x, y))
		return;
	if (ToolEvents::Pressed(button, state, x, y))
		return;
}
/// Tracks mouse position, gives info to a tool if needed
void mouse_motion(int x, int y)
{
	cursorX = x;
	cursorY = y;
	if (ToolEvents::Hover(x, y))
		return;
}
/// Initializes Toolbar and Canvas, Sets up the camera mode
void init()
{
	canvasAssigned = true;
	currentCanvas = NewCanvas(500, 500, 100, 100);
	Toolbar::Init();
	gluOrtho2D(0, 720, 0, 720);
}
/// Used to Reprint the Screen
void idle()
{
	glutPostRedisplay();
}
/// The main GLUT function
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// Double Buffered,RGB
	glutInitWindowSize(720, 720);		// window size
	glutCreateWindow("Computer Graphics Project");//title
	glutDisplayFunc(display);
	glutMouseFunc(mouse_click);			// mouse handler
	glutPassiveMotionFunc(mouse_motion);// mouse not clicked
	glutMotionFunc(mouse_motion);		// mouse clicked
	glutIdleFunc(idle);					// redisplay
	init();
	glutMainLoop();						// start printing
	return 0;
}
