/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "PlayArea.h"

PlayArea::PlayArea()
	: m_cards(8)
{
	for (int i = 0; i < m_cards.Length(); ++i)
		m_cards[i].Push(Card());
}

PlayArea::PlayArea(const PlayArea & copy)
	: m_cards(copy.m_cards)
{}

PlayArea::~PlayArea()
{}


PlayArea & PlayArea::operator=(const PlayArea & rhs)
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
bool PlayArea::IsValid(const Card & card, int dest)
{
	bool valid = ((m_cards[dest].Peek().Rank() == NONE) ||
				((GetColor(card) != GetColor(m_cards[dest].Peek())) &&
				(card.Rank() == (m_cards[dest].Peek().Rank() - 1))));

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
void PlayArea::AddCard(Card card, int dest)
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
Card PlayArea::TakeCard(int src)
{
	Card card;
	if (m_cards[src].Peek().Rank() != NONE)
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
const Card & PlayArea::SeeCard(int src) const
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
int PlayArea::OpenCells(int dest)
{
	int open = 0;

	for (int i = 0; i < m_cards.Length(); ++i)
	{
		if (i != dest && m_cards[i].Peek().Rank() == NONE)
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
int PlayArea::ValidDepth(int src)
{
	int depth = 1;
	bool valid = true;

	LStack<Card> temp;
	while (m_cards[src].Peek().Rank() != NONE && valid)
	{
		temp.Push(m_cards[src].Pop());

		valid = ((GetColor(m_cards[src].Peek()) != GetColor(temp.Peek())) && // diff color
			m_cards[src].Peek().Rank() == temp.Peek().Rank() + 1);			 // one rank higher

		depth += valid;
	}

	while (!temp.isEmpty())
		m_cards[src].Push(temp.Pop());

	return depth;
}

/************************************************************************
* Purpose: To get the "color" of a card
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the card is a "red" card
*************************************************************************/
bool PlayArea::GetColor(const Card & card)
{
	return (card.Suit() <= DIAMONDS);
}