/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Deck.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef DECK_H
#define DECK_H

#include "Array.h"
#include "AStack.h"
#include "Card.h"

#define DECK_SIZE 52

/************************************************************************
* Class: Deck
*
* Purpose: This class provides convenience methods for working with a deck
*			of 52 standard playing cards
*
* Manager functions:
*	Deck();
*	Deck(const Deck & copy);
*	~Deck()
*	Deck & operator=(const Deck & rhs);
*
* Methods:
*
*************************************************************************/
class Deck
{
public:
	Deck();
	Deck(const Deck & copy);
	~Deck();

	Deck & operator=(const Deck & rhs);

	void Shuffle(unsigned int seed = 0);
	void Reset();

	Card DrawCard();
	bool isEmpty();

private:
	void BuildDeck();
	
	Array<Card> m_original;
	Array<Card> m_shuffle;
	AStack<Card> m_deck;
};

#endif // DECK_H
