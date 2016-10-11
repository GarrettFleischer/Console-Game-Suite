/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	1/15/16
* Modifications: 2/2/16 - Greatly improved drawing efficiency
*************************************************************************/

#include "Console.h"

#include <cstring>

///////////////////////////////////////////////////////////////
//	INITIALIZE SINGLETON
//////

Console Console::m_instance = Console();

//////
//	END INITIALIZE SINGLETON
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	CTORS AND DTOR
//////

// PRIVATE
Console::Console(UINT width, UINT height, BOOL visiblity, UINT encoding)
	: m_ohandle(GetStdHandle(STD_OUTPUT_HANDLE)), m_ihandle(GetStdHandle(STD_INPUT_HANDLE)), m_width(width), m_height(height), m_buffer(nullptr)
{
	// Ensure that the console is in the correct encoding
	SetEncoding(encoding);

	// Ensure that the console can receive mouse events...
	EnableMouseEvents();

	// Resize the window
	Resize(width + 20, height + 20);

	// Cursor visibility
	SetCursorVisibility(visiblity);
}

Console::Console(const Console & copy)
{}

Console & Console::operator=(const Console & console)
{
	return *this;
}

Console::~Console()
{
	delete[] m_instance.m_buffer;
	m_instance.m_buffer = nullptr;
}

//////
//	END CTORS AND DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC STATIC METHODS
//////

/************************************************************************
* Purpose: To create a color of the specified foreground and background
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The specified color
*************************************************************************/
COLOR Console::MakeColor(COLOR foreground, COLOR background)
{
	return (foreground + MakeBackground(background));
}

/************************************************************************
* Purpose: To create a color of the specified background
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The specified background with a black foreground
*************************************************************************/
COLOR Console::MakeBackground(COLOR background)
{
	return background * 16;
}

//////
//	END PUBLIC STATIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: To write a single character to the console at a specified position
*
* Precondition:
*		draw - whether or not to defer rendering
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Write(int x, int y, const char & c, COLOR color)
{
	if (InBounds(x, y))
	{
		SetCursor(x, y);

		int index = (m_instance.m_cursor.X + (m_instance.m_cursor.Y * m_instance.m_width));
		m_instance.m_buffer[index].Char.AsciiChar = c;
		m_instance.m_buffer[index].Attributes = color;

		m_instance.m_update = true;
	}
}

/************************************************************************
* Purpose: To write a string of characters to the console at a specified position
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Write(int x, int y, const char * txt, COLOR color)
{
	for (UINT i = 0; i < strlen(txt); ++i)
		Write(x + i, y, txt[i], color);

	m_instance.m_update = true;
}

/************************************************************************
* Purpose: To completely clear the screen with the given color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Clear(COLOR color)
{
	ClearBuffer(m_instance.m_buffer, (m_instance.m_width * m_instance.m_height), MakeBackground(color));
	m_instance.m_update = true;
}

/************************************************************************
* Purpose: To clear a line on the screen with the given color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::ClearLine(int line, COLOR color)
{
	if (line < m_instance.m_height)
	{
		int y = (line * m_instance.m_width);
		for (int i = y; i < y + m_instance.m_width && i < (m_instance.m_width * m_instance.m_height); ++i)
		{
			m_instance.m_buffer[i].Char.AsciiChar = ' ';
			m_instance.m_buffer[i].Attributes = color;
		}

		m_instance.m_update = true;
	}
}

/************************************************************************
* Purpose: To clear a region on the screen with the given color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::ClearRect(int x1, int y1, int x2, int y2, COLOR color)
{
	for (int y = y1; y < y2 && y < m_instance.m_height; ++y)
	{
		for (int x = x1; x < x2 && x < m_instance.m_width; ++x)
		{
			if (InBounds(x, y))
			{
				int index = (x + (y * m_instance.m_width));
				m_instance.m_buffer[index].Char.AsciiChar = ' ';
				m_instance.m_buffer[index].Attributes = color;
			}
		}
	}

	m_instance.m_update = true;
}

/************************************************************************
* Purpose: To check if a given coordinate is within the bounds of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given coordinate is inside the bounds of the console
*************************************************************************/
bool Console::InBounds(int x, int y)
{
	return (((x >= 0) && (x < m_instance.m_width)) && ((y >= 0) && (y < m_instance.m_height)));
}


/************************************************************************
* Purpose: To get the number of milliseconds since the last Update()
*
* Precondition:
*		Update() should be called at least once for accurate results
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The number of milliseconds since the last Update()
*************************************************************************/
float Console::DeltaTime()
{
	duration<float, std::milli> diff = (high_resolution_clock::now() - m_instance.m_lastUpdate);
	return diff.count();
}

/************************************************************************
* Purpose: To perform a busy wait for the specified number of milliseconds
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Wait(double ms)
{
	if (ms > 0)
	{
		time_point_t start = high_resolution_clock::now();
		duration<float, std::milli> diff(0);

		while (diff.count() < ms)
			diff = (high_resolution_clock::now() - start);
	}
}

/************************************************************************
* Purpose: To perform any necessary drawing
*
* Precondition:
*		m_instance.m_update is TRUE
*
* Postcondition:
*		Modifies:	m_instance.m_update and the console screen
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Update()
{
	m_instance.m_lastUpdate = high_resolution_clock::now();

	if (m_instance.m_update)
	{
		m_instance.m_update = false;
		Draw();
	}
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS AND SETTERS
//////

/************************************************************************
* Purpose: To change whether or not the blinking cursor is visible
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console cursor info
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::SetCursorVisibility(BOOL visible)
{
	GetConsoleCursorInfo(m_instance.m_ohandle, &m_instance.m_cinf);
	m_instance.m_cinf.bVisible = visible;
	SetConsoleCursorInfo(m_instance.m_ohandle, &m_instance.m_cinf);
}

/************************************************************************
* Purpose: To change the encoding of all characters on the screen
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::SetEncoding(UINT encoding)
{
	SetConsoleCP(encoding);
	SetConsoleOutputCP(encoding);
}

/************************************************************************
* Purpose: To resize BOTH the console window and the screen buffer
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*					The screen will be completely cleared with a white foreground and black background
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Resize(UINT width, UINT height)
{
	// inner size
	m_instance.m_csbi.srWindow.Left = 0;
	m_instance.m_csbi.srWindow.Top = 0;
	m_instance.m_csbi.srWindow.Right = width - 1;
	m_instance.m_csbi.srWindow.Bottom = height - 1;
	// buffer size
	SetConsoleScreenBufferSize(m_instance.m_ohandle, { static_cast<SHORT>(width), static_cast<SHORT>(height) });

	// window size
	SetConsoleWindowInfo(m_instance.m_ohandle, TRUE, &m_instance.m_csbi.srWindow);

	// new buffer with new size
	CHAR_INFO * temp = new CHAR_INFO[width * height];
	ClearBuffer(temp, width * height, MakeColor(Color::white, Color::black));

	// update old buffer
	delete[] m_instance.m_buffer;
	m_instance.m_buffer = temp;

	// set the new width and height
	m_instance.m_width = width;
	m_instance.m_height = height;

	// redraw the screen
	m_instance.m_update = true;
}

/************************************************************************
* Purpose: To get the position of the text cursor in the window
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The position of the text cursor
*************************************************************************/
Coord Console::GetCursor()
{
	return m_instance.m_cursor;
}

/************************************************************************
* Purpose: To set the position of the text cursor in the window
*
* Precondition:
*
* Postcondition:
*		Modifies:	The position of the text cursor
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::SetCursor(int x, int y)
{
	m_instance.m_cursor.X = x;
	m_instance.m_cursor.Y = y;
	Bound(m_instance.m_cursor.X, m_instance.m_cursor.Y);

	SetConsoleCursorPosition(m_instance.m_ohandle, m_instance.m_cursor);
}

/************************************************************************
* Purpose: To move the text cursor relative to its current position
*
* Precondition:
*
* Postcondition:
*		Modifies:	The position of the text cursor
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::MoveCursor(int dx, int dy)
{
	m_instance.m_cursor.X += dx;
	m_instance.m_cursor.Y += dy;
	Bound(m_instance.m_cursor.X, m_instance.m_cursor.Y);

	SetConsoleCursorPosition(m_instance.m_ohandle, m_instance.m_cursor);
}

/************************************************************************
* Purpose: To get the current width of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current width of the console
*************************************************************************/
int Console::Width()
{
	return m_instance.m_width;
}

/************************************************************************
* Purpose: To get the current height of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current height of the console
*************************************************************************/
int Console::Height()
{
	return m_instance.m_height;
}

/************************************************************************
* Purpose: To get the output handle of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The output handle of the console
*************************************************************************/
HANDLE & Console::OutputHandle()
{
	return m_instance.m_ohandle;
}

/************************************************************************
* Purpose: To get the input handle of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The input handle of the console
*************************************************************************/
HANDLE & Console::InputHandle()
{
	return m_instance.m_ihandle;
}

//////
//	END GETTERS AND SETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

/************************************************************************
* Purpose: To set the console mode to accept mouse events
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console mode
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::EnableMouseEvents()
{
	DWORD dwPreviousMode;
	GetConsoleMode(m_instance.m_ohandle, &dwPreviousMode);

	DWORD dwNewMode = dwPreviousMode | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS & ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(m_instance.m_ohandle, dwNewMode);
}

/************************************************************************
* Purpose: To clear out the given buffer with null characters of the specified color
*
* Precondition:
*
* Postcondition:
*		Modifies:	The given buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::ClearBuffer(CHAR_INFO * buffer, UINT size, COLOR color)
{
	for (UINT i = 0; i < size; ++i)
	{
		buffer[i].Char.AsciiChar = '\0';
		buffer[i].Attributes = color;
	}
}

/************************************************************************
* Purpose: To bound a given set of coordinates to the width and height of the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	The given coordinates
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Bound(int & x, int & y)
{
	if (x < 0)
		x = 0;
	else if (x >= int(m_instance.m_width))
		x = m_instance.m_width - 1;

	if (y < 0)
		y = 0;
	else if (y >= int(m_instance.m_height))
		y = m_instance.m_height - 1;
}

/************************************************************************
* Purpose: To write the local buffer to the screen buffer
*
* Precondition:
*
* Postcondition:
*		Modifies:	The screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Console::Draw()
{
	SMALL_RECT consoleWriteArea = m_instance.m_csbi.srWindow;
	WriteConsoleOutputA(m_instance.m_ohandle, m_instance.m_buffer, { static_cast<SHORT>(m_instance.m_width), static_cast<SHORT>(m_instance.m_height) }, { 0, 0 }, &consoleWriteArea);
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////