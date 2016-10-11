/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "MoveCardAction.h"

MoveCardAction::MoveCardAction(FCBoard & board, FCBoard::AREA from, FCBoard::AREA to, int src, int dest, int depth)
	: m_board(board), m_from(from), m_to(to), m_src(src), m_dest(dest), m_depth(depth)
{}

void MoveCardAction::Undo()
{
	m_board.MoveCards(m_to, m_from, m_dest, m_src, m_depth, false);
}

void MoveCardAction::Redo()
{
	m_board.MoveCards(m_from, m_to, m_src, m_dest, m_depth, false);
}

bool MoveCardAction::Contains(void * item)
{
	bool contains = false;

	if (item == &m_board)
		contains = true;

	return contains;
}
