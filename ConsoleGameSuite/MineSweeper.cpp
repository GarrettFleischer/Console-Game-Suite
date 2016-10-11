/************************************************************************
* Author:		Garrett Fleischer
* Filename:		MineSweeper.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#include "MineSweeper.h"

///////////////////////////////////////////////////////////////
//	INITIALIZE STATIC VARS
//////
const double MineSweeper::PI = (atan(1) * 4);

#define SMILE "\x01"
#define DEAD  "\x02"
#define HEART "\x03"

//////
//	END INITIALIZE STATIC VARS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	CTORS AND DTOR
//////

MineSweeper::MineSweeper()
	: m_menu(4), m_onMenu(true), m_paused(false), m_firstClick(true), m_clicks(0), m_mines(0), m_flags(0)
{
	// Rename console window
	SetConsoleTitle(L"Bomb Scrubber");

	// Set the Console to the appropriate size
	CResize(100, 50);

	// Instantiate all menu buttons
	CreateMenus();

	// Display the Main Menu
	ShowMenu();
}

MineSweeper::MineSweeper(const MineSweeper & copy)
{
	*this = copy;
}

MineSweeper::~MineSweeper()
{
	Cleanup();
	m_menu.Purge();
}

//////
//	END CTORS AND DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

MineSweeper & MineSweeper::operator=(const MineSweeper & rhs)
{
	m_board = rhs.m_board;
	m_cellButtons = rhs.m_cellButtons;
	m_mineCoords = rhs.m_mineCoords;

	m_menu = rhs.m_menu;
	m_btnQuit = rhs.m_btnQuit;
	m_btnReset = rhs.m_btnReset;
	m_btnScore = rhs.m_btnScore;

	m_onMenu = rhs.m_onMenu;
	m_paused = rhs.m_paused;
	m_gameRunning = rhs.m_gameRunning;

	m_difficulty = rhs.m_difficulty;
	m_firstClick = rhs.m_firstClick;
	m_clicks = rhs.m_clicks;
	m_mines = rhs.m_mines;
	m_flags = rhs.m_flags;

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: To allow an outside game loop to update this game
*
* Precondition:
*		Assumes that Mouse::UpdateMouseState() 
*		And that Keyboard::UpdateKeyboardState() has already been called
*
* Postcondition:
*		Modifies:	Game state, buttons, and console screen buffer
*		Throws:		N/A
*		Returns:	TRUE if the user has not quit the game
*************************************************************************/
bool MineSweeper::Update()
{
	// If the game is active
	if (m_gameRunning)
	{
		// Only update game if there was a mouse event
		if (Mouse::Moved() || Mouse::BtnPressed(Mouse::LEFT) || Mouse::BtnPressed(Mouse::RIGHT))
			UpdateGame();

		UpdateMenus();
	}

	return m_gameRunning;
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

///////////////////////////////////////////////////////////////
//	UI
//////

/************************************************************************
* Purpose: To update either the Main or Game menu Buttons
*
* Precondition:
*		Assumes that Mouse::UpdateMouseState() and
*		Keyboard::UpdateKeyboardState() have already been called
*
* Postcondition:
*		Modifies:	Game state, buttons, and console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::UpdateMenus()
{
	if (m_onMenu)
	{
		// Update Main Menu
		for (int i = 0; i < m_menu.Length(); ++i)
		{
			m_menu[i].Update();

			if (m_menu[i].Clicked(Mouse::LEFT))
				MenuButtonClicked(m_menu[i]);
		}
	}
	else
	{
		// Update Game Menu:
		m_btnQuit.Update();
		m_btnReset.Update();

		// Check if user wants to restart this level
		if (!m_firstClick && (Keyboard::KeyPressed('R') || m_btnReset.Clicked(Mouse::LEFT)))
		{
			Cleanup();
			ShowGame();
		}

		// Check if user wants to return to Main Menu
		if (Keyboard::KeyPressed('Q') || m_btnQuit.Clicked(Mouse::LEFT))
		{
			Cleanup();
			ShowMenu();
		}
	}
}

/************************************************************************
* Purpose: To update either the Main or Game menu Buttons
*
* Precondition:
*		Assumes that Mouse::UpdateMouseState() and
*		Keyboard::UpdateKeyboardState() have already been called
*
* Postcondition:
*		Modifies:	Game state, cell buttons, and console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::UpdateGame()
{
	if (!m_paused)
	{
		// Update the cells
		for (int y = 0; y < m_cellButtons.Rows(); ++y)
		{
			for (int x = 0; x < m_cellButtons.Columns(); ++x)
			{
				m_cellButtons[y][x].Update();

				// Handle left click
				if (m_cellButtons[y][x].Clicked(Mouse::LEFT))
					CellButtonClicked(m_cellButtons[y][x]);

				// Handle right click
				if (m_cellButtons[y][x].Clicked(Mouse::RIGHT))
					CellButtonRightClicked(m_cellButtons[y][x]);
			}
		}
	}
}

/************************************************************************
* Purpose: To clear the screen and display the main menu
*
* Precondition:
*
* Postcondition:
*		Modifies:	Console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::ShowMenu()
{
	m_onMenu = true;

	CClear();

	string oborder_h = string(CWidth() * 3 / 4, '=');
	string iborder_h = string(CWidth() * 3 / 4, '*');

	// DRAW BORDER
	CWrite(CWidth() / 8, CHeight() / 4 - 1, oborder_h.c_str());
	CWrite(CWidth() / 8, CHeight() * 3 / 4 + 1, oborder_h.c_str());

	CWrite(CWidth() / 8, CHeight() / 4, iborder_h.c_str());
	CWrite(CWidth() / 8, CHeight() * 3 / 4, iborder_h.c_str());

	// DRAW TEXT
	CWrite(CWidth() / 2 - 10, CHeight() / 4 - 1, " BOMB SCRUBBER! ");
	CWrite(CWidth() / 2 - 11, CHeight() * 3 / 4 + 1, " Use your mouse! ");

	for (int i = 0; i < m_menu.Length(); ++i)
		m_menu[i].Draw();
}

/************************************************************************
* Purpose: To reset the game with the correct difficulty and then display it
*
* Precondition:
*
* Postcondition:
*		Modifies:	Console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::ShowGame()
{
	int columns, rows;

	m_paused = false;
	m_clicks = 0;
	m_flags = 0;
	
	string difficulty_message;
	switch (m_difficulty)
	{
	case BEGINNER:
		columns = 10;
		rows = 10;
		m_mines = 10;
		difficulty_message = "Arg ye lily livered, yeller bellied, casual scrub!";
		break;

	case INTERMEDIATE:
		columns = 16;
		rows = 16;
		m_mines = 40;
		difficulty_message = "Arg ye slightly above average scrub!";
		break;

	case EXPERT:
		columns = 30;
		rows = 16;
		m_mines = 100;
		difficulty_message = "Feeling extra salty today, eh scrub? It does me scrubber heart good it does, arg...";
		break;
	}

	m_cellButtons.Resize(rows, columns);
	m_board.Resize(rows, columns);
	m_mineCoords.SetLength(m_mines);

	CClear();

	ShowMessage(difficulty_message, CMakeColor(Color::bright_white));

	// MENU BUTTONS
	m_btnQuit.Draw();
	m_btnReset.SetText(SMILE);
	m_btnReset.SetColors(Color::grey, Color::yellow, Color::white, Color::yellow);
	SetClicks(0);

	// CELL BUTTONS
	for (int x = 0; x < columns; ++x)
	{
		for (int y = 0; y < rows; ++y)
		{
			m_cellButtons[y][x] = Button(x * CELL_WIDTH + OFFSET_X, y * CELL_HEIGHT + OFFSET_Y, 0, "", Color::white, 0, Color::cyan, 0);
			m_cellButtons[y][x].Resize(CELL_WIDTH, CELL_HEIGHT);
		}
	}
}

/************************************************************************
* Purpose: To display a message at the bottom of the screen
*
* Precondition:
*		m_cellButtons must already be instantiated for the message to
*		show in the correct location
*
* Postcondition:
*		Modifies:	Console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::ShowMessage(const string & message, COLOR color)
{
	int line = ((m_cellButtons.Rows() * CELL_HEIGHT) + OFFSET_Y + 2);
	CClearLine(line);
	CClearLine(line + 2);
	CWrite(5, line, message.c_str(), color);
	CWrite(5, line + 2, "Press \"Q\" to return to Menu, \"R\" to Restart, or \"Esc\" to Exit...");
}

/************************************************************************
* Purpose: To update the score button with the appropriate text
*
* Precondition:
*
* Postcondition:
*		Modifies:	Console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::SetClicks(int clicks)
{
	m_clicks = clicks;
	string txt = string("Clicks: ").append(to_string(m_clicks));
	m_btnScore.SetText(txt);
}

/************************************************************************
* Purpose: To instantiate all Main and Game menu Buttons
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_menu and m_btn* Buttons
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::CreateMenus()
{
	// Instantiate Main Menu Buttons
	// and ensure that they are all the same width...
	m_menu[BEGINNER] = Button(40, 17, BEGINNER, "Easy");
	m_menu[BEGINNER].Resize(16, 3);

	m_menu[INTERMEDIATE] = Button(40, 21, INTERMEDIATE, "Intermediate");
	m_menu[INTERMEDIATE].Resize(16, 3);

	m_menu[EXPERT] = Button(40, 25, EXPERT, "Hard");
	m_menu[EXPERT].Resize(16, 3);

	m_menu[QUIT] = Button(40, 29, QUIT, "Quit");
	m_menu[QUIT].Resize(16, 3);

	// Instantiate Game Menu Buttons
	m_btnQuit = Button(OFFSET_X + 1, OFFSET_Y - 4, 0, "X", Color::dark_red, Color::white, Color::red, Color::bright_white);
	m_btnReset = Button(OFFSET_X + 8, OFFSET_Y - 4, 0, SMILE, Color::grey, Color::yellow, Color::white, Color::yellow);
	m_btnScore = Button(OFFSET_X + 15, OFFSET_Y - 4, 0, "Clicks: 0", Color::white, Color::blue, Color::white, Color::blue);
}

/************************************************************************
* Purpose: To handle a main menu button click
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::MenuButtonClicked(Button & btn)
{
	if (btn.ID() == QUIT)
	{
		m_gameRunning = false;
	}
	else
	{
		m_onMenu = false;
		m_difficulty = DIFFICULTY(btn.ID());
		ShowGame();
	}
}

/************************************************************************
* Purpose: To handle a cell button click
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::CellButtonClicked(Button & btn)
{
	int x = (btn.X() - OFFSET_X) / CELL_WIDTH,
		y = (btn.Y() - OFFSET_Y) / CELL_HEIGHT;

	if (m_firstClick)
	{
		m_firstClick = false;
		SetClicks(++m_clicks);
		Populate(x, y);
	}
	else
	{
		if (!IsChecked(x, y) && !IsFlagged(x, y))
		{
			SetClicks(++m_clicks);
		}
	}

	UncoverCell(x, y);
	CheckVictory();
	
}

/************************************************************************
* Purpose: To handle a cell button right click
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::CellButtonRightClicked(Button & btn)
{
	int x = (btn.X() - OFFSET_X) / CELL_WIDTH,
		y = (btn.Y() - OFFSET_Y) / CELL_HEIGHT;

	FlagCell(x, y);
	CheckVictory();
}

//////
//	END UI
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	CELL LOGIC
//////

bool MineSweeper::IsMine(int x, int y)
{
	return (m_board[y][x].Value() == Cell::MINE);
}

bool MineSweeper::IsChecked(int x, int y)
{
	return m_board[y][x].Checked();
}

bool MineSweeper::IsEmpty(int x, int y)
{
	return (m_board[y][x].Value() == 0);
}

bool MineSweeper::IsFlagged(int x, int y)
{
	return m_board[y][x].Flagged();
}

/************************************************************************
* Purpose: To calculate the value of a cell based on surrounding MINE cells
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The calculated value
*************************************************************************/
int MineSweeper::CalcCellValue(int x, int y)
{
	int value = Cell::MINE;

	if (m_board[y][x].Value() != Cell::MINE)
	{
		value = 0;

		// Check the surrounding cells in the 8 cardinal directions
		for (int i = 0; i < 8; ++i)
		{
			int dx = x + int(round(cos((PI / 4) * i)));
			int dy = y + int(round(sin((PI / 4) * i)));

			if (m_board.Contains(dy, dx))
				value += IsMine(dx, dy);
		}
	}

	return value;
}

/************************************************************************
* Purpose: To calculate the foreground color of a cell based on a given value
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The calculated foreground color
*************************************************************************/
COLOR MineSweeper::CalcCellColor(int value)
{
	COLOR foreground = Color::grey;

	if (value > 0)
	{
		if (value == 1)
			foreground = Color::blue;
		else if (value == 2)
			foreground = Color::green;
		else if (value == 3)
			foreground = Color::dark_red;
		else if (value == 4)
			foreground = Color::dark_blue;
		else if (value == 5)
			foreground = Color::purple;
		else if (value == 6)
			foreground = Color::turquoise;
		else if (value == 7)
			foreground = Color::lime;
		else if (value == 8)
			foreground = Color::red;
	}

	return foreground;
}

/************************************************************************
* Purpose: To uncover a cell that has been clicked on, and recursively uncover
*			valid surrounding cells
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::UncoverCell(int x, int y)
{
	// Uncover this cell
	if (m_board.Contains(y, x) && !IsChecked(x, y) && !IsFlagged(x, y))
	{
		if (IsMine(x, y))
		{
			LoseGame(x, y);
		}
		else
		{
			// CELL
			m_board[y][x].SetChecked(true);

			// CELL BUTTON
			int value = m_board[y][x].Value();
			COLOR foreground = CalcCellColor(value);

			m_cellButtons[y][x].SetColors(Color::grey, foreground, Color::grey, foreground);

			if (value > 0)
				m_cellButtons[y][x].SetText(to_string(value), false);
		}
	}

	if (IsEmpty(x, y) && !IsFlagged(x, y))
	{
		// Uncover the surrounding cells in the 8 cardinal directions
		for (int i = 0; i < 8; ++i)
		{
			int dx = x + int(round(cos((PI / 4) * i)));
			int dy = y + int(round(sin((PI / 4) * i)));

			if (m_board.Contains(dy, dx) && !IsMine(dx, dy) && !IsChecked(dx, dy))
				UncoverCell(dx, dy);
		}
	}
}

/************************************************************************
* Purpose: To toggle the flagged value of a cell
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::FlagCell(int x, int y)
{
	if (!IsChecked(x, y))
	{
		m_board[y][x].SetFlagged(!IsFlagged(x, y));

		if (IsFlagged(x, y))
		{
			m_flags++;
			m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::dark_red, Color::red);
			m_cellButtons[y][x].SetText("P", false);
		}
		else
		{
			// Punish indecisive flags...
			SetClicks(++m_clicks);
			m_flags--;
			m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::cyan, Color::red);
			m_cellButtons[y][x].SetText("", false);
		}
	}
}

//////
//	END CELL LOGIC
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GAME LOGIC
//////

/************************************************************************
* Purpose: To determine if the user has won and if so, call WinGame()
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::CheckVictory()
{
	bool winning = false;

	// If you haven't placed more flags than mines
	if (m_flags <= m_mines)
	{
		// Check if all bombs have been flagged
		if (!m_firstClick && (m_flags == m_mines))
		{
			winning = true;

			for (int i = 0; i < m_mineCoords.Length() && winning; ++i)
			{
				if (!IsFlagged(m_mineCoords[i].X, m_mineCoords[i].Y))
					winning = false;
			}
		}

		// If the mines aren't all flagged 
		if (!winning)
		{
			winning = true;

			// Check if all squares have been uncovered
			for (int y = 0; y < m_board.Rows() && winning; ++y)
			{
				for (int x = 0; x < m_board.Columns() && winning; x++)
				{
					// If its not a mine and it hasn't been uncovered yet....
					if (!IsMine(x, y) && !IsChecked(x, y))
						winning = false;
				}
			}
		}
	}

	if (winning)
		WinGame();
}

/************************************************************************
* Purpose: To flag all remaining mines, and show a victory message
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::WinGame()
{
	// Flag all the mines
	for (int i = 0; i < m_mineCoords.Length(); ++i)
	{
		int x = m_mineCoords[i].X,
			y = m_mineCoords[i].Y;

		if (IsFlagged(x, y))
		{
			m_cellButtons[y][x].SetColors(Color::green, Color::red, Color::green, Color::red);
		}
		else
		{
			m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::white, Color::red);
			m_cellButtons[y][x].SetText("P", false);
		}
	}

	// Update the game menu
	m_btnReset.SetText(HEART);
	m_btnReset.SetColors(Color::grey, Color::pink, Color::white, Color::pink);
	SetClicks(m_clicks);

	// Write the Winning Message
	ShowMessage("Survival!", CMakeColor(Color::lime, Color::black));

	m_paused = true;
}

/************************************************************************
* Purpose: To display all remaining mines, and show a losing message
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::LoseGame(int mine_x, int mine_y)
{
	// Reveal all the mines
	for (int i = 0; i < m_mineCoords.Length(); ++i)
	{
		int x = m_mineCoords[i].X,
			y = m_mineCoords[i].Y;

		if (IsFlagged(x, y))
		{
			m_cellButtons[y][x].SetColors(Color::dark_red, Color::red, Color::dark_red, Color::red);
		}
		else
		{
			m_cellButtons[y][x].SetColors(Color::grey, Color::black, Color::grey, Color::black);
			m_cellButtons[y][x].SetText("*", false);
		}
	}

	// Mark the losing mine
	m_cellButtons[mine_y][mine_x].SetColors(Color::red, Color::black, Color::red, Color::black);

	// Update the Game Menu
	m_btnReset.SetText(DEAD);
	m_btnReset.SetColors(Color::grey, Color::black, Color::white, Color::black);

	// Write the Losing Message
	ShowMessage("Violent death! (And probable loss of limb)", CMakeColor(Color::red, Color::black));

	m_paused = true;
}

/************************************************************************
* Purpose: To populate the map with mines and calculate the values of
*			surrounding cells
*
* Precondition:
*		fc_x/y - coords of the first mouse click so as not to place a mine there
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::Populate(int fc_x, int fc_y)
{
	int columns = m_board.Columns(),
		rows = m_board.Rows();
	int x = -1,
		y = -1;
	
	// Seed rand()
	srand((unsigned)time(NULL));
	
	// Place mines
	for (int i = 0; i < m_mines; ++i)
	{
		// find a new cell while the current coords are invalid
		while (IsInvalidMineCoord(x, y, fc_x, fc_y))
		{
			x = rand() % columns;
			y = rand() % rows;
		}

		m_mineCoords[i] = { x, y };
		m_board[y][x].SetValue(Cell::MINE);
	}

	// Calculate values
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			m_board[y][x].SetValue(CalcCellValue(x, y));
		}
	}

}

/************************************************************************
* Purpose: To determine if the given coords are a valid spot for a new mine
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the coords are invalid
*************************************************************************/
bool MineSweeper::IsInvalidMineCoord(int x, int y, int fc_x, int fc_y)
{
	int width = (m_board.Columns() - 1);
	int height = (m_board.Rows() - 1);

	// first click spot
	bool fc_coord = ((x == fc_x) && (y == fc_y));

	// in one of the corners
	bool in_corner = ((x == 0)		&& (y == 0 || y == height)) ||
					  ((x == width) && (y == 0 || y == height));
					 
	return (!m_board.Contains(y, x) || IsMine(x, y) || fc_coord || in_corner);
}

/************************************************************************
* Purpose: To reset game state, Purge() all game related arrays, and
*			clear the screen
*
* Precondition:
*
* Postcondition:
*		Modifies:	Game state
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void MineSweeper::Cleanup()
{
	m_clicks = 0;
	m_firstClick = true;
	m_mines = 0;
	m_flags = 0;

	m_board.Purge();
	m_cellButtons.Purge();
	m_mineCoords.Purge();

	CClear();
}

//////
//	END GAME LOGIC
///////////////////////////////////////////////////////////////

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////