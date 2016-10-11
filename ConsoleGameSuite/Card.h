/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Card.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef CARD_H
#define CARD_H

#define HEARTS	 char(3)
#define DIAMONDS char(4)
#define CLUBS	 char(5)
#define SPADES	 char(6)

#define KING  13
#define QUEEN 12
#define JACK  11
#define ACE	  1
#define NONE  0

/************************************************************************
* Class: Card
*
* Purpose: This class represents a standard playing card
*
* Manager functions:
*	Card();
*	Card(const Card & copy);
*	~Card()
*	Card & operator=(const Card & rhs);
*
* Methods:
*	int Rank() const;
*	char Suit() const;
*
*************************************************************************/
class Card
{
public:
	Card(char suit = HEARTS, int rank = NONE);
	Card(const Card & copy);

	~Card();

	Card & operator=(const Card & rhs);
	bool operator==(const Card & rhs);

	int Rank() const;
	char Suit() const;

private:
	char m_suit;
	int m_rank;
};

#endif // CARD_H
