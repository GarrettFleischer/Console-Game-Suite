/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Board.h
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include "Array2D.h"
#include "Cell.h"

/************************************************************************
* Class: Board
*
* Purpose: This class inherits from an Array2D of Cells
*			Right now it is a simple pass through class, but has the potential for
*			appending helper methods down the line
*
* Manager functions:
*	Board(int rows = 0, int columns = 0)
*
*	Board(const Board & copy)
*	operator=(const Board & rhs)
*
*	~Board()
*
* Methods:
*
*************************************************************************/
class MSBoard : public Array2D<Cell>
{
public:
	// CTORS AND DTOR
	MSBoard(int rows = 0, int columns = 0);
	MSBoard(const MSBoard & copy);
	
	virtual ~MSBoard();

	// OPERATORS
	virtual MSBoard & operator=(const MSBoard & rhs);

private:

};

#endif // BOARD_H

