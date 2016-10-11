/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Cell.h
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef CELL_H
#define CELL_H


/************************************************************************
* Class: Cell
*
* Purpose: This class maintains data for a cell in a MineSweeper game
*
* Manager functions:
*	Cell(int rows = 0, int columns = 0)
*
*	Cell(const Cell & copy)
*	operator=(const Cell & rhs)
*
*	~Cell()
*
* Methods:
*	Setters and Getters for the members
*
*************************************************************************/
class Cell
{
public:
	static const int MINE = -1;

	// CTORS AND DTOR
	Cell(int value = 0);
	Cell(const Cell & copy);
	~Cell();

	// OPERATORS
	Cell & operator=(const Cell & rhs);

	// GETTERS AND SETTERS
	int Value() const;
	void SetValue(int value);

	bool Checked() const;
	void SetChecked(bool checked);

	bool Flagged() const;
	void SetFlagged(bool flagged);

private:
	// MEMBERS
	int m_value;
	bool m_checked;
	bool m_flagged;

};


#endif // CELL_H
