/************************************************************************
* Author:		Garrett Fleischer
* Filename:		MineSweeper.h
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <time.h>
#include <string>
using std::string;
using std::to_string;

#include "Console.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Button.h"

#include "MSBoard.h"

/************************************************************************
* Class: MineSweeper
*
* Purpose: This class is responsible for managing and displaying a
*			MineSweeper game with MOUSE INPUT
*
* Manager functions:
*	MineSweeper(int rows = 0, int columns = 0)
*
*	MineSweeper(const MineSweeper & copy)
*	operator=(const MineSweeper & rhs)
*
*	~MineSweeper()
*
* Methods:
*	Update()
*		to update the state of the Game and its Buttons
*
*************************************************************************/
class MineSweeper
{
public:
	// CTORS AND DTOR
	MineSweeper();
	MineSweeper(const MineSweeper & copy);

	~MineSweeper();

	// OPERATORS
	MineSweeper & operator=(const MineSweeper & rhs);

	// METHODS
	bool Update();

private:
	// ENUMS, CONSTANTS, AND STATICS
	enum DIFFICULTY { BEGINNER, INTERMEDIATE, EXPERT };
	static const int QUIT = 3;

	static const double PI;
	static const int CELL_WIDTH = 3;
	static const int CELL_HEIGHT = 2;
	static const int OFFSET_X = 6;
	static const int OFFSET_Y = 10;

	// METHODS
		// UI
		void UpdateMenus();
		void UpdateGame();
		void ShowMenu();
		void ShowGame();
		void ShowMessage(const string & message, COLOR color = Color::white);
		void SetClicks(int clicks);

		void CreateMenus();
		void MenuButtonClicked(Button & btn);
		void CellButtonClicked(Button & btn);
		void CellButtonRightClicked(Button & btn);
	
		// CELL LOGIC
		bool IsMine(int x, int y);
		bool IsChecked(int x, int y);
		bool IsEmpty(int x, int y);
		bool IsFlagged(int x, int y);

		int CalcCellValue(int x, int y);
		COLOR CalcCellColor(int value);

		void UncoverCell(int x, int y);
		void FlagCell(int x, int y);
	
		// GAME LOGIC
		void CheckVictory();
		void WinGame();
		void LoseGame(int mine_x, int mine_y);

		void Populate(int fc_x, int fc_y);
		bool IsInvalidMineCoord(int x, int y, int fc_x, int fc_y);
		void Cleanup();
	
	// MEMBERS
	MSBoard m_board;
	Array2D<Button> m_cellButtons;
	Array<Coord> m_mineCoords;

	Array<Button> m_menu;
	Button m_btnQuit;
	Button m_btnReset;
	Button m_btnScore;

	bool m_onMenu;
	bool m_paused;
	bool m_gameRunning;

	DIFFICULTY m_difficulty;
	bool m_firstClick;
	int m_clicks;
	int m_mines;
	int m_flags;
};


#endif // MINESWEEPER_H
