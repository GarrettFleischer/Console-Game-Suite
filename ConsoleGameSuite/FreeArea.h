/************************************************************************
* Author:		Garrett Fleischer
* Filename:		FreeArea.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef FREEAREA_H
#define FREEAREA_H

#include "Area.h"
#include "Array.h"

/************************************************************************
* Class: FreeArea
*
* Purpose: This class represents the "Free" area of the Freecell game
*
* Manager functions:
*	FreeArea();
*	FreeArea(const FreeArea & copy);
*	virtual ~FreeArea()
*	FreeArea & operator=(const FreeArea & rhs);
*
* Methods:
*	all inherited
*************************************************************************/

class FreeArea : public Area
{
public:
	FreeArea();
	FreeArea(const FreeArea & copy);

	virtual ~FreeArea();

	FreeArea & operator=(const FreeArea & rhs);

	virtual bool IsValid(const Card & card, int dest);
	virtual void AddCard(Card card, int dest);
	virtual Card TakeCard(int src);
	virtual const Card & SeeCard(int src) const;
	virtual int OpenCells(int dest = -1);
	virtual int ValidDepth(int dest);

private:
	Array<Card> m_cards;

};

#endif // FREEAREA_H
