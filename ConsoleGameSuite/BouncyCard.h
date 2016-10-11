/************************************************************************
* Author:		Garrett Fleischer
* Filename:		BouncyCard.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef BOUNCYCARD_H
#define BOUNCYCARD_H

#include "Console.h"
#include "CardBtn.h"

/************************************************************************
* Class: BouncyCard
*
* Purpose: This class draws a bouncing card on the screen
*
* Manager functions:
*	BouncyCard();
*	BouncyCard(const BouncyCard & copy);
*	~BouncyCard()
*	BouncyCard & operator=(const BouncyCard & rhs);
*
* Methods:
*	void Update();
*	void Draw();
*	bool IsDone();
*
*************************************************************************/
class BouncyCard
{
public:
	static const int SIZE = 9;

	BouncyCard(float x = 0, float y = 0, float hspeed = 0, float vspeed = 0, Card card = Card());
	BouncyCard(const BouncyCard & copy);
	~BouncyCard();

	BouncyCard & operator=(const BouncyCard & rhs);

	void Update();
	void Draw();

	bool IsDone() const;

private:
	const float GRAVITY = 0.02f;

	float m_x;
	float m_y;
	float m_hspeed;
	float m_vspeed;
	bool m_done;

	CardBtn m_card;
};


#endif // BOUNCYCARD_H
