/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Freecell.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef FREECELL_H
#define FREECELL_H

#include "View.h"

#include "FCBoard.h"
#include "Array.h"
#include "CardBtn.h"
#include "BouncyCard.h"

#define FREE_CELLS 4
#define HOME_CELLS 4
#define PLAY_CELLS 8

/************************************************************************
* Class: Freecell
*
* Purpose: This class is the View for displaying a FCBoard model
*			It is also in charge of handling user input, and victory conditions
*
* Manager functions:
*	Freecell();
*	Freecell(const Freecell & copy);
*	~Freecell()
*	Freecell & operator=(const Freecell & rhs);
*
* Methods:
*
*************************************************************************/
class Freecell : public View
{
public:
	static const int OFF_X = CardBtn::SIZE;
	static const int OFF_Y = 3;
	static const int TOTAL_CARDS = 68; // to hold all 52 CardBtns + 16 empty cards

	Freecell();
	Freecell(FCBoard::SCENARIO scenario);
	Freecell(const Freecell & copy);

	virtual ~Freecell();

	Freecell & operator=(const Freecell & rhs);

	bool Update();

protected:
	virtual void ModelUpdated();

private:
	void Draw();

	void DrawFreeArea();
	void DrawHomeArea();
	void DrawPlayArea();
	void DrawScore();

	void DeselectAll();

	void CheckVictory();
	void BounceCards();

	float RandomRange(float low, float high);

	bool m_running;
	bool m_wonGame;
	Array<CardBtn> m_cards;
	FCBoard m_board;

	CardBtn * m_selected;
	bool m_moved;

	BouncyCard * m_bounce;
};

#endif // FREECELL_H
