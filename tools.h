/// class for handling tool behaviour on mouse click
class ToolEvents
{
public:
	/// displays the toolbar
	static void Display(int window_width, int window_height);
	/// mouse clicked on toolbar or not
	static bool Pressed(int button, int state, int x, int y);
	/// mouse over toolbar or not (clicked/not clicked both)
	static bool Hover(int x, int y);
};
/// class for pencil tool
class Tool_Pen
{
public:
	/// mouse still pressed?
	static bool isMouseDown;
	/// last x position of mouse
	static int mouseLastX;
	/// last y position of mouse
	static int mouseLastY;
	/// mouse clicked on toolbar or not
	static bool Pressed(int button, int state, int cx, int cy);
	/// mouse over tool or not (clicked/not clicked both)
	static bool Hover(int x, int y);
};
/// class for fill tool
class Tool_Fill
{
public:
	/// fill function
	static void Fill(Colour startColour, int x, int y);
	/// mouse clicked on toolbar or not
	static bool Pressed(int button, int state, int x, int y);
};
///  class for rectangle tool
class Tool_Rect
{
public:
	/// mouse still pressed?
	static bool isMouseDown;
	/// last x position of mouse
	static int startMouseX;
	/// last y position of mouse
	static int startMouseY;
	/// mouse clicked on tool or not
	static bool Pressed(int button, int state, int cx, int cy);
};
/// class for circle tool
class Tool_Circ
{
public:
	/// mouse still pressed?
	static bool isMouseDown;
	/// last x position of mouse
	static int startMouseX;
	/// last x position of mouse
	static int startMouseY;
	/// mouse clicked on toolbar or not
	static bool Pressed(int button, int state, int cx, int cy);
};
/// class for handling the toolbar where tools are present
class Toolbar
{
public:
	/// selected tool index
	static int selectedButton; 	
	/// Pencil button	
	static Button penButton;	
	/// Fill button	
	static Button fillButton;
	/// Rectangle button 		
	static Button rectButton;
	/// Circle button		
	static Button circleButton;		
	/// handles event if a tool is clicked on
	static void ToolButtonPressed(Button button)
	{
		if (button.text == "Pencil")
			selectedButton = 0;
		if (button.text == "Fill")
			selectedButton = 1;
		if (button.text == "Rect")
			selectedButton = 2;
		if (button.text == "Ellipse")
			selectedButton = 3;
	}
	/// toolbar initialization
	static void Init()
	{
		selectedButton = 0;
		penButton = Button::Create(0, 100, 90, 40, (char *)"Pencil", ToolButtonPressed);
		fillButton = Button::Create(0, 140, 90, 40, (char *)"Fill", ToolButtonPressed);
		rectButton = Button::Create(0, 180, 90, 40, (char *)"Rect", ToolButtonPressed);
		circleButton = Button::Create(0, 220, 90, 40, (char *)"Ellipse", ToolButtonPressed);
	}
	/// to draw the toolbar on screen
	static void Display(int window_width, int window_height)
	{
		penButton.Display(window_width, window_height);
		fillButton.Display(window_width, window_height);
		rectButton.Display(window_width, window_height);
		circleButton.Display(window_width, window_height);
	}
	/// Responsible for mouse input
	///
	/// Checks if pointer is pressed
	/// gets mouse coordinates
	/// Calls appropriate function
	static bool Pressed(int button, int state, int x, int y)
	{
		if ((selectedButton != 0) && (penButton.Pressed(button, state, x, y)))
			return true;
		if ((selectedButton != 1) && (fillButton.Pressed(button, state, x, y)))
			return true;
		if ((selectedButton != 2) && (rectButton.Pressed(button, state, x, y)))
			return true;
		if ((selectedButton != 3) && (circleButton.Pressed(button, state, x, y)))
			return true;
		return false;
	}
};
/// Responsible for mouse Press
///
/// Checks if pointer is pressed/released/inside canvas/outside canvas
/// gets mouse coordinates
/// Calls appropriate function
bool ToolEvents::Pressed(int button, int state, int x, int y)
{
	switch (Toolbar::selectedButton)
	{
	case 0:
		if (Tool_Pen::Pressed(button, state, x, y))
			return true;
		break;
	case 1:
		if (Tool_Fill::Pressed(button, state, x, y))
			return true;
		break;
	case 2:
		if (Tool_Rect::Pressed(button, state, x, y))
			return true;
		break;
	case 3:
		if (Tool_Circ::Pressed(button, state, x, y))
			return true;
		break;
	}
	return false;
}
/// Passes mouse movement events onto the selected tool
bool ToolEvents::Hover(int x, int y)
{
	switch (Toolbar::selectedButton)
	{
	case 0:
		if (Tool_Pen::Hover(x, y))
			return true;
		break;
	}
	return false;
}