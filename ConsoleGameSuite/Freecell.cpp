/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "Freecell.h"

#include "FreeArea.h"
#include "HomeArea.h"
#include "PlayArea.h"

#include "Console.h"
#include "Button.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "HistoryManager.h"

#include <string>
using std::string;
using std::to_string;


Freecell::Freecell()
	: m_cards(TOTAL_CARDS), m_selected(nullptr), m_running(true), m_wonGame(false), m_bounce(nullptr)
{
	SetModel(&m_board);
}

Freecell::Freecell(FCBoard::SCENARIO scenario)
	: m_cards(TOTAL_CARDS), m_selected(nullptr), m_running(true), m_wonGame(false), m_board(scenario), m_bounce(nullptr)
{
	SetModel(&m_board);
}

Freecell::Freecell(const Freecell & copy)
	: m_running(copy.m_running), m_board(copy.m_board), m_cards(copy.m_cards), m_moved(copy.m_moved), m_selected(nullptr)
{
	SetModel(&m_board);
}

Freecell::~Freecell()
{
	// in case user exits in the middle of bouncing...
	delete m_bounce;
	m_bounce = nullptr;
}

Freecell & Freecell::operator=(const Freecell & rhs)
{
	if (this != &rhs)
	{
		m_board = rhs.m_board;
		m_cards = rhs.m_cards;
		m_moved = rhs.m_moved;
		m_wonGame = rhs.m_wonGame;
		m_running = rhs.m_running;
		m_selected = nullptr;

		SetModel(&m_board);
	}

	return *this;
}


/************************************************************************
* Purpose: To update the state of all CardBtns and handle user input
*			Also calls updates BouncyCards through BounceCards()
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the game is still running
*************************************************************************/
bool Freecell::Update()
{
	bool clicked = false;

	m_running = !Keyboard::KeyPressed(VK_ESCAPE);

	if (m_wonGame)
	{
		BounceCards();
	}
	else if (m_running)
	{
		for (int i = 0; i < m_cards.Length(); ++i)
		{
			CardBtn & cb = m_cards[i];
			cb.Update();

			if (cb.Clicked(Mouse::LEFT))
			{
				if (m_selected == nullptr)
				{
					clicked = true;
					m_moved = false;
					if (!cb.IsEmpty() && cb.Depth() > 0)
					{
						m_selected = &cb;
						cb.SetSelected(true);
						if (cb.Depth() > 1)
						{
							for (int i = 0; i < m_cards.Length(); ++i)
							{
								if (m_cards[i].Area() == cb.Area() && m_cards[i].Row() == cb.Row() && m_cards[i].Depth() < cb.Depth())
									m_cards[i].SetSelected(true);
							}
						}
					}
				}
				else if (!m_moved)
				{
					m_moved = true;
					m_board.MoveCards(m_selected->Area(), cb.Area(), m_selected->Row(), cb.Row(), m_selected->Depth());
					CheckVictory();
				}
			}
		}

		if (!clicked && Mouse::BtnPressed(Mouse::LEFT))
		{
			m_selected = nullptr;
			DeselectAll();
		}
	}

	return m_running;
}

/************************************************************************
* Purpose: To redraw this view if the model was updated
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::ModelUpdated()
{
	m_selected = nullptr;
	DeselectAll();
	Draw();
}

/************************************************************************
* Purpose: To redraw everything
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::Draw()
{
	CClear(Color::green);

	// Free area
	DrawFreeArea();

	// Home area
	DrawHomeArea();

	// Play area
	DrawPlayArea();

	// Scoreboard
	DrawScore();
}

/************************************************************************
* Purpose: To draw all CardBtns in the FreeArea
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::DrawFreeArea()
{
	FreeArea * free = dynamic_cast<FreeArea *>(m_board.GetArea(FCBoard::FREE));
	if (free)
	{
		int width = CardBtn::SIZE + 1;

		for (int i = 0; i < FREE_CELLS; ++i)
		{
			Card c = free->SeeCard(i);
			string disp = to_string(c.Rank()) + c.Suit();
			COLOR col = ((c.Suit() <= DIAMONDS) ? Color::dark_red : Color::black);

			CardBtn & cb = m_cards[i];
			int x = OFF_X + i * width;
			int y = OFF_Y;

			cb.SetPos(x, y, Color::green);
			cb.Large();
			cb.SetCard(c);
			cb.SetRow(i);
			cb.SetArea(FCBoard::FREE);
		}
	}
}

/************************************************************************
* Purpose: To draw all CardBtns in the HomeArea
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::DrawHomeArea()
{
	HomeArea * home = dynamic_cast<HomeArea *>(m_board.GetArea(FCBoard::HOME));

	if (home)
	{
		int width = CardBtn::SIZE + 1;

		for (int i = 0; i < HOME_CELLS; ++i)
		{
			Card c = home->SeeCard(i);
			string disp = to_string(c.Rank()) + c.Suit();


			CardBtn & cb = m_cards[i + FREE_CELLS];
			int x = OFF_X + i * width + FREE_CELLS * width + width / 2;
			int y = OFF_Y;

			cb.SetPos(x, y, Color::green);
			cb.Large();
			cb.SetCard(c);
			cb.SetRow(i);
			cb.SetArea(FCBoard::HOME);

			COLOR col = (((i + HEARTS) <= DIAMONDS) ? Color::dark_red : Color::blue);
			CClearRect(x + 2, y - 2, x + width - 3, y - 1, CMakeBackground(Color::white));
			CWrite(x + width / 2 - 1, y - 2, char(i + HEARTS), CMakeColor(col, Color::white));
		}
	}
}

/************************************************************************
* Purpose: To draw all CardBtns in the PlayArea
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::DrawPlayArea()
{
	PlayArea * play = dynamic_cast<PlayArea *>(m_board.GetArea(FCBoard::PLAY));

	if (play)
	{
		int width = CardBtn::SIZE + 1;

		int total = 0;
		for (int i = 0; i < PLAY_CELLS; ++i)
		{
			LStack<Card> temp;
			while (play->SeeCard(i).Rank() != NONE)
				temp.Push(play->TakeCard(i));

			temp.Push(play->TakeCard(i));

			int depth = temp.Size();

			int cards = 0;
			while (!temp.isEmpty())
			{
				Card c = temp.Pop();
				string disp = to_string(c.Rank()) + c.Suit();
				COLOR col = ((c.Suit() <= DIAMONDS) ? Color::dark_red : Color::black);

				CardBtn & cb = m_cards[FREE_CELLS + HOME_CELLS + total++];
				int x = OFF_X + 2 + i * width;
				int y = OFF_Y + cards++ * 2 + width + 2 - (cards > 0) * 2;

				cb.SetPos(x, y, Color::green);
				cb.SetCard(c);
				cb.SetDepth(depth--);
				cb.SetRow(i);
				cb.SetArea(FCBoard::PLAY);

				if (temp.Size() > 0)
					cb.Small();
				else
					cb.Large();

				play->AddCard(c, i);
			}
		}

		// hide extra cards
		for (total += FREE_CELLS + HOME_CELLS; total < m_cards.Length(); ++total)
		{
			m_cards[total].SetPos(-width, -width, Color::green, false);
		}

		// ensure that all cards are displayed
		for (int i = 0; i < m_cards.Length(); i++)
		{
			m_cards[i].Draw();
		}
	}
}

/************************************************************************
* Purpose: To draw the scoreboard
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::DrawScore()
{
	CWrite(CWidth() / 2 - 5, CHeight() - 4, (string("Moves: ") + to_string(m_board.Moves())).c_str(), CMakeColor(Color::bright_white, Color::green));
	CWrite(CWidth() / 2 - 15, CHeight() - 2, "Press Esc to return to menu", CMakeColor(Color::bright_white, Color::green));

	//TODO: DISPLAY THE GAME NUMBER OF THE CURRENT GAME
}

/************************************************************************
* Purpose: To deselect all selected cards
*
* Precondition:
*		Should be called after cards have been moved, or a blank area of the board clicked
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::DeselectAll()
{
	for (int i = 0; i < m_cards.Length(); ++i)
		m_cards[i].SetSelected(false);
}

/************************************************************************
* Purpose: Checks if the user won the game and sets a flag if so
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::CheckVictory()
{
	HomeArea * home = dynamic_cast<HomeArea *>(m_board.GetArea(FCBoard::HOME));

	if (home)
	{
		bool victory = true;

		for (int i = 0; i < HOME_CELLS && victory; ++i)
		{
			LStack<Card> temp;
			while (home->SeeCard(i).Rank() != NONE)
				temp.Push(home->TakeCard(i));

			if (temp.Size() < KING)
				victory = false;

			while (!temp.isEmpty())
				home->AddCard(temp.Pop(), i);
		}

		if (victory)
		{
			// disable undo/redo events
			HistoryManager::PollEvents(false);
			m_wonGame = true;
			srand((unsigned)time(NULL));
		}
	}
}

/************************************************************************
* Purpose: To update bouncy cards after the game has been won
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Freecell::BounceCards()
{
	static int index = 0;
	static int cards = 0;
	static int pass = 0;

	// if we've bounced all the cards...
	if (!m_running || cards >= DECK_SIZE)
	{
		// re-enable undo/redo events
		HistoryManager::PollEvents(true);
		index = 0;
		cards = 0;
		pass = 0;
		m_running = false;
		CWait(800);
	}
	else
	{
		if (m_bounce)
		{
			m_bounce->Update();

			if (m_bounce->IsDone())
			{
				delete m_bounce;
				m_bounce = nullptr;
				++cards;
			}
		}
		else
		{
			if (m_board.GetArea(FCBoard::HOME)->SeeCard(index).Rank() != NONE)
			{
				int width = CardBtn::SIZE + 1;
				float x = float(OFF_X + index * width + FREE_CELLS * width + width / 2);
				float y = float(OFF_Y);
				float hspeed = 0;
				while (abs(hspeed) < 0.05)
					hspeed = RandomRange(-0.8f, 0.5f);

				float vspeed = RandomRange(-1, 0);

				Card c = m_board.GetArea(FCBoard::HOME)->TakeCard(index);

				m_bounce = new BouncyCard(x, y, hspeed, vspeed, c);
				CWait(100);
			}

			index += 2;
			if (index > 3)
			{
				pass = (pass + 1) % 2;
				index = pass;
			}
		}
	}
}

float Freecell::RandomRange(float low, float high)
{
	return (low + (static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)))));
}
