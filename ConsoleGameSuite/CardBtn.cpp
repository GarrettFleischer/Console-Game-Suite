/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "CardBtn.h"


CardBtn::CardBtn()
	: m_rank(NONE), m_suit(""), m_color(Color::grey), m_depth(1), m_row(0), m_selected(false), m_area(FCBoard::PLAY)
{
	SetPos(-SIZE, -SIZE, 0, false);
	Small();
	SetColors(Color::white, m_color, Color::bright_white, m_color);
	SetText(m_suit, false);
}

CardBtn::CardBtn(const Card & card)
	: m_rank(NONE), m_suit(""), m_color(Color::grey)
{
	SetPos(-SIZE, -SIZE, 0, false);
	Small();
	SetCard(card);
}

CardBtn::CardBtn(const CardBtn & copy)
	: Button(copy), m_rank(copy.m_rank), m_suit(copy.m_suit), m_color(copy.m_color),
	m_depth(copy.m_depth), m_row(copy.m_row), m_selected(copy.m_selected), m_area(copy.m_area)
{}

CardBtn::~CardBtn()
{}

CardBtn & CardBtn::operator=(const CardBtn & rhs)
{
	if (this != &rhs)
	{
		Button::operator=(rhs);
		m_rank = rhs.m_rank;
		m_suit = rhs.m_suit;
		m_color = rhs.m_color;
		m_depth = rhs.m_depth;
		m_row = rhs.m_row;
		m_area = rhs.m_area;
		m_selected = rhs.m_selected;


		SetColors(Color::white, m_color, Color::bright_white, m_color);
		if (m_rank != NONE)
			SetText(m_suit, false);
		else
			SetText("", false);
	}

	return *this;
}

/************************************************************************
* Purpose: To change the card this button represents
*
* Precondition:
*
* Postcondition:
*		Modifies:	Rank, Suit, Color, and Text
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void CardBtn::SetCard(const Card & card)
{
	m_rank = card.Rank();
	m_suit = card.Suit();
	m_color = ((card.Suit() <= DIAMONDS) ? Color::dark_red : Color::blue);

	SetColors(Color::white, m_color, Color::bright_white, m_color);
	if (m_rank != NONE)
		SetText(m_suit, false);
	else
		SetText("", false);
}


void CardBtn::SetDepth(int depth)
{
	m_depth = depth;
}

int CardBtn::Depth() const
{
	return m_depth;
}

void CardBtn::SetRow(int row)
{
	m_row = row;
}

int CardBtn::Row() const
{
	return m_row;
}

void CardBtn::SetArea(FCBoard::AREA area)
{
	m_area = area;
}

FCBoard::AREA CardBtn::Area() const
{
	return m_area;
}

/************************************************************************
* Purpose: To display this card button to the screen
*
* Precondition:
*
* Postcondition:
*		Modifies:	Console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void CardBtn::Draw()
{	
	// EMPTY CARD
	if (m_rank == NONE)
	{
		if (m_height == SIZE)
		{
			SetColors(Color::green, Color::yellow, Color::green, Color::lime, false);
			Button::Draw();

			COLOR txt_back = (m_hover ? m_backgroundHover : m_background);
			COLOR txt_fore = (m_hover ? m_foregroundHover : m_foreground);

			// Horizontal lines
			for (int x = m_x + 1; x < m_x + m_width - 1; ++x)
			{
				CWrite(x, m_y, char(196), CMakeColor(txt_fore, txt_back));
				CWrite(x, m_y + m_height - 1, char(196), CMakeColor(txt_fore, txt_back));
			}

			// Vertical lines
			for (int y = m_y + 1; y < m_y + m_height - 1; ++y)
			{
				CWrite(m_x, y, char(179), CMakeColor(txt_fore, txt_back));
				CWrite(m_x + m_width - 1, y, char(179), CMakeColor(txt_fore, txt_back));
			}

			// Corners
			CWrite(m_x, m_y, char(218), CMakeColor(txt_fore, txt_back));
			CWrite(m_x + m_width - 1, m_y, char(191), CMakeColor(txt_fore, txt_back));
			CWrite(m_x + m_width - 1, m_y + m_height - 1, char(217), CMakeColor(txt_fore, txt_back));
			CWrite(m_x, m_y + m_height - 1, char(192), CMakeColor(txt_fore, txt_back));
		}
	}
	// NON-EMPTY CARD
	else
	{
		if (m_selected)
			SetColors(Color::turquoise, m_color, Color::turquoise, m_color, false);
		else
			SetColors(Color::white, m_color, Color::bright_white, m_color, false);

		Button::Draw();

		COLOR txt_back = (m_hover ? m_backgroundHover : m_background);
		COLOR txt_fore = (m_hover ? m_foregroundHover : m_foreground);

		string rank;
		switch (m_rank)
		{
		case KING:
			rank = "K";
			break;

		case QUEEN:
			rank = "Q";
			break;

		case JACK:
			rank = "J";
			break;

		case ACE:
			rank = "A";
			break;

		default:
			rank = std::to_string(m_rank);
			break;
		}

		// Small card
		if (m_height != SIZE)
		{
			// Horizontal line
			for (int x = m_x + 1; x < m_x + m_width - 1; ++x)
				CWrite(x, m_y, char(196), CMakeColor(txt_fore, txt_back));

			// Vertical lines
			CWrite(m_x, m_y + 1, char(179), CMakeColor(txt_fore, txt_back));
			CWrite(m_x + m_width - 1, m_y + 1, char(179), CMakeColor(txt_fore, txt_back));

			// Corners
			CWrite(m_x, m_y, char(218), CMakeColor(txt_fore, txt_back));
			CWrite(m_x + m_width - 1, m_y, char(191), CMakeColor(txt_fore, txt_back));

			// Rank
			CWrite(m_x + 1, m_y + 1, rank.c_str(), CMakeColor(txt_fore, txt_back));
		}

		// Large card
		else
		{
			// Horizontal lines
			for (int x = m_x + 1; x < m_x + m_width - 1; ++x)
			{
				CWrite(x, m_y, char(196), CMakeColor(txt_fore, txt_back));
				CWrite(x, m_y + m_height - 1, char(196), CMakeColor(txt_fore, txt_back));
			}

			// Vertical lines
			for (int y = m_y + 1; y < m_y + m_height - 1; ++y)
			{
				CWrite(m_x, y, char(179), CMakeColor(txt_fore, txt_back));
				CWrite(m_x + m_width - 1, y, char(179), CMakeColor(txt_fore, txt_back));
			}

			// Corners
			CWrite(m_x, m_y, char(218), CMakeColor(txt_fore, txt_back));
			CWrite(m_x + m_width - 1, m_y, char(191), CMakeColor(txt_fore, txt_back));
			CWrite(m_x + m_width - 1, m_y + m_height - 1, char(217), CMakeColor(txt_fore, txt_back));
			CWrite(m_x, m_y + m_height - 1, char(192), CMakeColor(txt_fore, txt_back));

			// Rank
			CWrite(m_x + 1, m_y + 1, rank.c_str(), CMakeColor(txt_fore, txt_back));
			CWrite(m_x + m_width - 2 - (m_rank == 10), m_y + m_height - 2, rank.c_str(), CMakeColor(txt_fore, txt_back));
		}
	}
}

/************************************************************************
* Purpose: To make this a full size card
*
* Precondition:
*
* Postcondition:
*		Modifies:	height of card
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void CardBtn::Large(COLOR background)
{
	Resize(SIZE, SIZE, background);
}

/************************************************************************
* Purpose: To make this a small 2-high card
*
* Precondition:
*
* Postcondition:
*		Modifies:	height of card
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void CardBtn::Small(COLOR background)
{
	Resize(SIZE, 2, background);
}

/************************************************************************
* Purpose: To toggle selection of this card
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void CardBtn::SetSelected(bool selected)
{
	m_selected = selected;

	Draw();
}

/************************************************************************
* Purpose: To tell if this is an empty cell
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the card's rank is NONE
*************************************************************************/
bool CardBtn::IsEmpty() const
{
	return (m_rank == NONE);
}
