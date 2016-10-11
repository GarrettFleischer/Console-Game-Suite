/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "BouncyCard.h"

BouncyCard::BouncyCard(float x, float y, float hspeed, float vspeed, Card card)
	: m_x(x), m_y(y), m_hspeed(hspeed), m_vspeed(vspeed), m_card(card), m_done(false)
{
	Draw();
	m_card.SetSelected(false);
	m_card.Large();
}

BouncyCard::BouncyCard(const BouncyCard & copy)
	: m_x(copy.m_x), m_y(copy.m_y), m_hspeed(copy.m_hspeed), m_vspeed(copy.m_vspeed),
	m_done(copy.m_done), m_card(copy.m_card)
{}

BouncyCard::~BouncyCard()
{}

BouncyCard & BouncyCard::operator=(const BouncyCard & rhs)
{
	if (this != &rhs)
	{
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_hspeed = rhs.m_hspeed;
		m_vspeed = rhs.m_vspeed;
		m_done = rhs.m_done;
		m_card = rhs.m_card;
	}

	return *this;
}

/************************************************************************
* Purpose: To move / bounce the card, and display it
*
* Precondition:
*
* Postcondition:
*		Modifies:	Position, speed, and IsDone()
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void BouncyCard::Update()
{
	if (!m_done)
	{
		m_vspeed += GRAVITY;
		m_x += m_hspeed;
		m_y += m_vspeed;

		// Bounce
		if (m_y > CHeight() - SIZE)
		{
			m_y = float(CHeight() - SIZE);
			m_vspeed = -(m_vspeed / 1.3f);
		}

		// Outside of the console window
		if ((m_y >= (CHeight() - SIZE) && abs(m_vspeed) <= GRAVITY) || (m_x < -SIZE || m_x > CWidth()))
			m_done = true;

		Draw();
	}
}

/************************************************************************
* Purpose: To display the card
*
* Precondition:
*
* Postcondition:
*		Modifies:	Console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void BouncyCard::Draw()
{
	m_card.SetPos((int)floor(m_x), (int)floor(m_y), 0, false);
	m_card.Draw();
}

/************************************************************************
* Purpose: To determine if the card has left the window, or stopped bouncing
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if this card is done
*************************************************************************/
bool BouncyCard::IsDone() const
{
	return m_done;
}
