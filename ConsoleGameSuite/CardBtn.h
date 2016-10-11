/************************************************************************
* Author:		Garrett Fleischer
* Filename:		CardBtn.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef CARDBTN_H
#define CARDBTN_H

#include "Card.h"
#include "Button.h"
#include "FCBoard.h"

/************************************************************************
* Class: CardBtn
*
* Purpose: This class draws an interactive playing card on the screen
*
* Manager functions:
*	CardBtn();
*	CardBtn(const CardBtn & copy);
*	~CardBtn()
*	CardBtn & operator=(const CardBtn & rhs);
*
* Methods:
*
*************************************************************************/

class CardBtn : public Button
{
public:
	static const int SIZE = 9;

	CardBtn();
	CardBtn(const Card & card);
	CardBtn(const CardBtn & copy);

	virtual ~CardBtn();

	CardBtn & operator=(const CardBtn & rhs);

	void SetCard(const Card & card);

	void SetDepth(int depth);
	int Depth() const;

	void SetRow(int row);
	int Row() const;

	void SetArea(FCBoard::AREA area);
	FCBoard::AREA Area() const;

	void Large(COLOR background = Color::green);
	void Small(COLOR background = Color::green);

	void SetSelected(bool selected);

	bool IsEmpty() const;

	virtual void Draw();

private:
	int m_rank;
	string m_suit;
	COLOR m_color;
	int m_depth;
	int m_row;
	FCBoard::AREA m_area;
	bool m_selected;
};

#endif // CARDBTN_H
