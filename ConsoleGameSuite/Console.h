/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.h
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

typedef high_resolution_clock::time_point time_point_t;

// TO AVOID NARROWING CONVERSION ERRORS IN VS 2015+
struct Coord
{
	int X;
	int	Y;

	operator COORD()
	{
		return{ static_cast<SHORT>(X), static_cast<SHORT>(Y) };
	}
};

// CONTAINS ALL AVAILABLE COLORS IN THE CONSOLE
typedef WORD COLOR;

struct Color
{
	static const COLOR
		black = 0,
		dark_blue = 1,
		green = 2,
		cyan = 3,
		dark_red = 4,
		purple = 5,
		dark_yellow = 6,
		white = 7,
		grey = 8,
		blue = 9,
		lime = 10,
		turquoise = 11,
		red = 12,
		pink = 13,
		yellow = 14,
		bright_white = 15;
};

// MACROS FOR COMMON STATIC FUNCTIONS
#define CMakeColor				Console::MakeColor
#define CMakeBackground			Console::MakeBackground
#define CWrite					Console::Write
#define CClear					Console::Clear
#define CClearLine				Console::ClearLine
#define CClearRect				Console::ClearRect
#define CInBounds				Console::InBounds
#define CDeltaTime				Console::DeltaTime
#define CWait					Console::Wait
#define CUpdate					Console::Update
#define CSetCursorVisibility	Console::SetCursorVisibility
#define CSetEncoding			Console::SetEncoding
#define CResize					Console::Resize
#define CGetCursor				Console::GetCursor
#define CSetCursor				Console::SetCursor
#define CMoveCursor				Console::MoveCursor
#define CWidth					Console::Width
#define CHeight					Console::Height
#define COutputHandle			Console::OutputHandle
#define CInputHandle			Console::InputHandle


/************************************************************************
* Class: Console
*
* Purpose: This class provides methods for manipulating the Windows console
*
* Manager functions:
*		GetInstance()
*
*	Private Console(UINT width = 80, UINT height = 40, BOOL visiblity = false, UINT encoding = 437)
*
*	~Console()
*
* Methods:
*	Public:
*		SetCursorVisibility(BOOL visiblity)
*			Set whether or not the cursor visibly blinks at its current location
*
*		SetConsoleEncoding(UINT encoding)
*			Change the encoding of characters displayed in the console
*
*		Resize(UINT width, UINT height)
*			Change the size of the window and screen buffer
*
*		CMakeColor(COLOR foreground = Color::white, COLOR background = Color::black)
*			Creates the Attribute value of foreground and background of a cell in the console
*
*		COLOR CMakeBackground(COLOR background)
*			Creates a color of the specified background with a black foreground
*
*		Write(Coord pos, const char & txt, COLOR color = Color::white, bool draw = true)
*			Writes a single character at the specified position. draw = whether or not to redraw the buffer
*
*		void Write(Coord pos, const char * txt, COLOR color = Color::white)
*			Writes a string to the console starting at the specified position. (does not wrap)
*
*	Private:
*		UpdatePosition(HANDLE & input_handle)
*
*************************************************************************/
class Console
{
public:
	// SINGLETON
	//static Console & GetInstance();

	// DTOR
	~Console();

	// STATIC METHODS
	static COLOR MakeColor(COLOR foreground = Color::white, COLOR background = Color::black);
	static COLOR MakeBackground(COLOR background);

	// METHODS
	static void Write(int x, int y, const char & txt, COLOR color = Color::white);
	static void Write(int x, int y, const char * txt, COLOR color = Color::white);

	static void Clear(COLOR color = Color::black);
	static void ClearLine(int line, COLOR color = Color::black);
	static void ClearRect(int x1, int y1, int x2, int y2, COLOR color = Color::black);

	static bool InBounds(int x, int y);

	static float DeltaTime();
	static void Wait(double ms);

	static void Update();

	// GETTERS AND SETTERS
	static void SetCursorVisibility(BOOL visiblity);
	static void SetEncoding(UINT encoding);

	static void Resize(UINT width, UINT height);

	static Coord GetCursor();
	static void SetCursor(int x, int y);
	static void MoveCursor(int dx, int dy);

	static int Width();
	static int Height();

	static HANDLE & OutputHandle();
	static HANDLE & InputHandle();

private:
	// CTORS
	Console(UINT width = 80, UINT height = 40, BOOL visiblity = false, UINT encoding = 437);
	Console(const Console & copy);

	// OPERATOR
	Console & operator=(const Console & console);

	// METHODS
	static void EnableMouseEvents();

	static void ClearBuffer(CHAR_INFO * buffer, UINT size, COLOR color);

	static void Bound(int & x, int & y);

	static void Draw();

	// SINGLETON
	static Console m_instance;

	// MEMBERS
	HANDLE						m_ohandle;
	HANDLE						m_ihandle;
	CONSOLE_SCREEN_BUFFER_INFO	m_csbi;
	CHAR_INFO *					m_buffer;
	CONSOLE_CURSOR_INFO			m_cinf;
	Coord						m_cursor;
	int							m_width;
	int							m_height;
	bool						m_update;
	time_point_t				m_lastUpdate;
};


#endif // CONSOLE_H
