/************************************************************************
* Author:		Garrett Fleischer
* Filename:		PlayArea.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef PLAYAREA_H
#define PLAYAREA_H

#include "Area.h"
#include "Array.h"
#include "LStack.h"

/************************************************************************
* Class: PlayArea
*
* Purpose: This class represents the "Play" area of the Freecell game
*
* Manager functions:
*	PlayArea();
*	PlayArea(const PlayArea & copy);
*	virtual ~PlayArea()
*	PlayArea & operator=(const PlayArea & rhs);
*
* Methods:
*	all inherited
*************************************************************************/
class PlayArea : public Area
{
public:
	PlayArea();
	PlayArea(const PlayArea & copy);

	virtual ~PlayArea();

	PlayArea & operator=(const PlayArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);
	virtual const Card & SeeCard(int src) const;
	virtual int OpenCells(int dest = -1);
	virtual int ValidDepth(int dest);

private:
	bool GetColor(const Card & card);

	Array<LStack<Card>> m_cards;

};

#endif // PLAYAREA_H
