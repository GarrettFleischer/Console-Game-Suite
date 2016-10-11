/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Area.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef AREA_H
#define AREA_H

#include "Card.h"

/************************************************************************
* Class: Area
*
* Purpose: This class is an interface for Freecell areas
*
* Manager functions:
*
*	virtual ~Area()
*
* Methods:
*		virtual bool IsValid(const Card & card, int dest)
*		virtual void AddCard(Card card, int dest)
*		virtual Card TakeCard(int src)
*		virtual const Card & SeeCard(int src) const
*		virtual int OpenCells(int dest = -1)
*		virtual int ValidDepth(int dest)
*************************************************************************/
class Area
{
public:
	virtual ~Area() {};

	virtual bool IsValid(const Card & card, int dest) = 0;
	virtual void AddCard(Card card, int dest) = 0;
	virtual Card TakeCard(int src) = 0;
	virtual const Card & SeeCard(int src) const = 0;
	virtual int OpenCells(int dest = -1) = 0;
	virtual int ValidDepth(int dest) = 0;
};


#endif // AREA_H
