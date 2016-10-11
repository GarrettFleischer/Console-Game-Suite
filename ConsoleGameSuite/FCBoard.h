/************************************************************************
* Author:		Garrett Fleischer
* Filename:		FCBoard.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef FCBOARD_H
#define FCBOARD_H

#include "Model.h"
#include "Array.h"
#include "Area.h"
#include "Deck.h"

/************************************************************************
* Class: FCBoard
*
* Purpose: This class is the model for the Frecell game
*			it acts as an interface between the game and the three areas
*
* Manager functions:
*	FCBoard();
*	FCBoard(const FCBoard & copy);
*	~FCBoard()
*	FCBoard & operator=(const FCBoard & rhs);
*
* Methods:
*
*************************************************************************/
class FCBoard : public Model
{
public:
	enum AREA { FREE, HOME, PLAY };
	enum SCENARIO { VICTORY, STACKS };

	FCBoard();
	FCBoard(const FCBoard & copy);
	FCBoard(SCENARIO scenario);
	virtual ~FCBoard();

	FCBoard & operator=(const FCBoard & rhs);

	bool MoveCards(AREA from, AREA to, int src, int dest, int depth, bool check_valid = true);

	int Moves() const;

	Area * GetArea(AREA area);

private:
	void DeepCopy(const FCBoard & copy);

	Array<Area *> m_areas;
	int m_moves;
};

#endif // FCBOARD_H
