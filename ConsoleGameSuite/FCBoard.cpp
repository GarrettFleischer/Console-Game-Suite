/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "FCBoard.h"

#include "FreeArea.h"
#include "HomeArea.h"
#include "PlayArea.h"

#include "HistoryManager.h"
#include "MoveCardAction.h"


FCBoard::FCBoard()
	: m_areas(3), m_moves(0)
{
	m_areas[FREE] = new FreeArea;
	m_areas[HOME] = new HomeArea;
	m_areas[PLAY] = new PlayArea;

	Deck d;
	d.Shuffle();
	for (int i = 0; i < DECK_SIZE; ++i)
		m_areas[PLAY]->AddCard(d.DrawCard(), i % 8);
}


FCBoard::FCBoard(const FCBoard & copy)
	: m_areas(3), m_moves(copy.m_moves)
{
	DeepCopy(copy);
}

/************************************************************************
* Purpose: To initialize the board with custom scenarios (for testing)
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
FCBoard::FCBoard(SCENARIO scenario)
	: m_areas(3), m_moves(0)
{
	m_areas[FREE] = new FreeArea;
	m_areas[HOME] = new HomeArea;
	m_areas[PLAY] = new PlayArea;

	switch (scenario)
	{
	case VICTORY:
		for (int i = 0; i < 4; ++i)
		{
			// fill first 4 home rows up to Queen
			for (int j = ACE; j <= QUEEN; ++j)
			{
				m_areas[HOME]->AddCard(Card(HEARTS + i, j), i);
			}
			
			// place remaining kings in play area
			m_areas[PLAY]->AddCard(Card(HEARTS + i, KING), i + 4);
		}
		break;

	case STACKS:
		// Make some nice stacks for moving lots of cards around
		for (int i = KING; i > ACE; --i)
		{
			m_areas[PLAY]->AddCard(Card(DIAMONDS + i % 2, i), 0);
		}
		m_areas[PLAY]->AddCard(Card(CLUBS, ACE), 1);

		for (int i = 2; i < 8; ++i)
			m_areas[PLAY]->AddCard(Card(CLUBS - i % 2, i + 5), i);

		m_areas[PLAY]->AddCard(Card(DIAMONDS, ACE), 7);
		break;
	}
}

FCBoard::~FCBoard()
{
	delete m_areas[FREE];
	delete m_areas[HOME];
	delete m_areas[PLAY];

	HistoryManager::RemoveActions(this);
}

FCBoard & FCBoard::operator=(const FCBoard & rhs)
{
	if (this != &rhs)
	{
		m_moves = rhs.m_moves;

		delete m_areas[FREE];
		delete m_areas[HOME];
		delete m_areas[PLAY];

		DeepCopy(rhs);
		Notify();
	}

	return *this;
}


/************************************************************************
* Purpose: To move "depth" number of cards "from" one area at the given "src" index
*			"to" another area at the given "dest" index
*
* Precondition:
*		By default, this function checks the validity of a move
*		if the move is valid: the cards are moved else they are left alone
*		a MoveCardAction() is also added to the HistoryManager
*		
*		if check_valid is false: the cards are moved regardless of validity
*		a MoveCardAction() is NOT added to the HistoryManager
*
*		TODO: return a value to represent the exact error!
*
* Postcondition:
*		Modifies:	Cards in the specified Areas
*		Throws:		N/A
*		Returns:	TRUE if the move was valid
*************************************************************************/
bool FCBoard::MoveCards(AREA from, AREA to, int src, int dest, int depth, bool check_valid)
{
	int f_dest = (to == FREE ? dest : -1);
	int p_dest = (to == PLAY ? dest : -1);

	int open_play = m_areas[PLAY]->OpenCells(p_dest);
	int open_free = m_areas[FREE]->OpenCells(f_dest);
	int open_cells = ((open_play * open_free) + (open_free + open_play) + 1);

	bool valid = (open_cells >= depth && depth <= m_areas[from]->ValidDepth(src));
	if (from != to)
		valid = valid && (depth <= m_areas[to]->ValidDepth(dest));
	else if(src == dest)
		valid = false;

	if (valid || !check_valid)
	{
		AStack<Card> temp(depth);
		for (int i = 0; i < depth; ++i)
			temp.Push(m_areas[from]->TakeCard(src));

		valid = m_areas[to]->IsValid(temp.Peek(), dest);

		while (!temp.isEmpty())
		{
			if (valid || !check_valid)
				m_areas[to]->AddCard(temp.Pop(), dest);
			else
				m_areas[from]->AddCard(temp.Pop(), src);
		}

		if (valid || !check_valid)
			m_moves++;

		Notify();
	}

	// only add an undo action if we are not performing undo and the move is valid
	if (check_valid && valid)
		HistoryManager::AddAction(new MoveCardAction(*this, from, to, src, dest, depth));

	return valid;
}

int FCBoard::Moves() const
{
	return m_moves;
}

Area * FCBoard::GetArea(AREA area)
{
	return m_areas[area];
}

void FCBoard::DeepCopy(const FCBoard & copy)
{
	m_areas[FREE] = new FreeArea(*((FreeArea *)copy.m_areas[FREE]));
	m_areas[HOME] = new HomeArea(*((HomeArea *)copy.m_areas[HOME]));
	m_areas[PLAY] = new PlayArea(*((PlayArea *)copy.m_areas[PLAY]));
}

