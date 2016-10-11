/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "Card.h"

Card::Card(char suit, int rank)
	: m_suit(suit), m_rank(rank)
{}

Card::Card(const Card & copy)
	: m_suit(copy.m_suit), m_rank(copy.m_rank)
{}

Card::~Card()
{}

Card & Card::operator=(const Card & rhs)
{
	if (this != &rhs)
	{
		m_suit = rhs.m_suit;
		m_rank = rhs.m_rank;
	}

	return *this;
}

bool Card::operator==(const Card & rhs)
{
	return ((m_suit == rhs.m_suit) && (m_rank == rhs.m_rank));
}

char Card::Suit() const
{
	return m_suit;
}

int Card::Rank() const
{
	return m_rank;
}
