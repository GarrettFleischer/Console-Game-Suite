/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "Deck.h"
#include <random>
#include <time.h>


Deck::Deck()
	: m_original(DECK_SIZE), m_shuffle(DECK_SIZE), m_deck(DECK_SIZE)
{
	BuildDeck();
}

Deck::Deck(const Deck & copy)
	: m_original(copy.m_original), m_shuffle(copy.m_shuffle), m_deck(copy.m_deck)
{}


Deck::~Deck()
{}

Deck & Deck::operator=(const Deck & rhs)
{
	if (this != &rhs)
	{
		m_shuffle = rhs.m_shuffle;
		m_deck = rhs.m_deck;
	}

	return *this;
}

/************************************************************************
* Purpose: To shuffle the cards in this deck based on a given seed
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_shuffle and m_deck
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Deck::Shuffle(unsigned int seed)
{
	if (seed == 0)
		seed = (unsigned)time(NULL);

	srand(seed);

	m_shuffle = m_original;
	while (!m_deck.isEmpty())
		m_deck.Pop();

	// shuffle cards around 156 times
	for (int i = 0; i < 156; ++i)
	{
		int c1 = rand() % m_original.Length();
		int c2 = rand() % m_original.Length();

		Card temp = m_shuffle[c1];
		m_shuffle[c1] = m_shuffle[c2];
		m_shuffle[c2] = temp;
	}

	for (int i = 0; i < m_shuffle.Length(); ++i)
		m_deck.Push(m_shuffle[i]);
}

/************************************************************************
* Purpose: To reset the deck back to an un-shuffled state
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_deck
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Deck::Reset()
{
	while (!m_deck.isEmpty())
		m_deck.Pop();

	for (int i = m_original.Length() - 1; i >= 0; --i)
		m_deck.Push(m_original[i]);
}

/************************************************************************
* Purpose: To grab a card off the top of the deck
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	the card on top of the deck
*************************************************************************/
Card Deck::DrawCard()
{
	return m_deck.Pop();
}

bool Deck::isEmpty()
{
	return m_deck.isEmpty();
}

/************************************************************************
* Purpose: To initialize the deck in order
*
* Precondition:
*
* Postcondition:
*		Modifies:	m_original, m_deck
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Deck::BuildDeck()
{
	for (char suit = HEARTS; suit <= SPADES; ++suit)
	{
		for (int rank = ACE; rank <= KING; ++rank)
		{
			int i = ((((suit - HEARTS) * KING) + rank) - 1);
			m_original[i] = Card(suit, rank);
		}
	}

	Reset();
}