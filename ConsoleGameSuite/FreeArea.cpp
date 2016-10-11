/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "FreeArea.h"

FreeArea::FreeArea()
	: m_cards(4)
{}

FreeArea::FreeArea(const FreeArea & copy)
	: m_cards(copy.m_cards)
{}

FreeArea::~FreeArea()
{}


FreeArea & FreeArea::operator=(const FreeArea & rhs)
{
	if(this != &rhs)
		m_cards = rhs.m_cards;

	return *this;
}


/************************************************************************
* Purpose: To determine if the given card can be placed on top of the destination stack
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the move is valid
*************************************************************************/
bool FreeArea::IsValid(const Card & card, int dest)
{
	return (m_cards[dest].Rank() == NONE);
}


/************************************************************************
* Purpose: To place a card on top of the destination index
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void FreeArea::AddCard(Card card, int dest)
{
	m_cards[dest] = card;
}

/************************************************************************
* Purpose: To take a card from the top of the destination index
*
* Precondition:
*
* Postcondition:
*		Modifies:	Removes the top card from the src stack
*		Throws:		N/A
*		Returns:	A copy of the card removed
*************************************************************************/
Card FreeArea::TakeCard(int src)
{
	Card card = m_cards[src];
	m_cards[src] = Card();

	return card;
}

/************************************************************************
* Purpose: To see the card on top of the destination index
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	A const ref to the card on the src stack
*************************************************************************/
const Card & FreeArea::SeeCard(int src) const
{
	return m_cards[src];
}

/************************************************************************
* Purpose: To quickly grab the number of empty cells 
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The number of empty cells
*************************************************************************/
int FreeArea::OpenCells(int dest)
{
	int open = 0;

	for (int i = 0; i < m_cards.Length(); ++i)
	{
		if (i != dest && m_cards[i].Rank() == NONE)
			open++;
	}

	return open;
}

/************************************************************************
* Purpose: To determine the maximum cards that can be taken from the dest 
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The number of cards that can be taken from the dest stack
*************************************************************************/
int FreeArea::ValidDepth(int dest)
{
	return 1;
}

