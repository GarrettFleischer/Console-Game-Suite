/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "HomeArea.h"

HomeArea::HomeArea()
	: m_cards(4)
{
	for (int i = 0; i < m_cards.Length(); ++i)
	{
		m_cards[i].Resize(53);
		m_cards[i].Push(Card());
	}
}

HomeArea::HomeArea(const HomeArea & copy)
	: m_cards(copy.m_cards)
{}

HomeArea::~HomeArea()
{}


HomeArea & HomeArea::operator=(const HomeArea & rhs)
{
	if (this != &rhs)
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
bool HomeArea::IsValid(const Card & card, int dest)
{
	bool valid = false;

	switch (dest)
	{
	case 0:
		valid = ((card.Suit() == HEARTS) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;

	case 1:
		valid = ((card.Suit() == DIAMONDS) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;

	case 2:
		valid = ((card.Suit() == CLUBS) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;

	case 3:
		valid = ((card.Suit() == SPADES) && (card.Rank() == (m_cards[dest].Peek().Rank() + 1)));
		break;
	}

	return valid;
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
void HomeArea::AddCard(Card card, int dest)
{
	m_cards[dest].Push(card);
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
Card HomeArea::TakeCard(int src)
{
	Card card;
	if(m_cards[src].Peek().Rank() != NONE)
		card = m_cards[src].Pop();

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
const Card & HomeArea::SeeCard(int src) const
{
	return m_cards[src].Peek();
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
int HomeArea::OpenCells(int dest)
{
	return 0;
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
int HomeArea::ValidDepth(int dest)
{
	return 1;
}

