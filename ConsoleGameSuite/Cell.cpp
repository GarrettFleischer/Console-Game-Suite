/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Cell.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#include "Cell.h"


///////////////////////////////////////////////////////////////
//	CTORS AND DTOR
//////

Cell::Cell(int value)
	: m_value(value), m_checked(false), m_flagged(false)
{}


Cell::Cell(const Cell & copy)
	: m_value(copy.m_value), m_checked(copy.m_checked)
{}

Cell::~Cell()
{
}

//////
//	END CTORS AND DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

Cell & Cell::operator=(const Cell & rhs)
{
	if (this != &rhs)
	{
		m_value = rhs.m_value;
		m_checked = rhs.m_checked;
	}

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	SETTERS AND GETTERS
//////

int Cell::Value() const
{
	return m_value;
}

void Cell::SetValue(int value)
{
	m_value = value;
}

bool Cell::Checked() const
{
	return m_checked;
}

void Cell::SetChecked(bool checked)
{
	m_checked = checked;
}

bool Cell::Flagged() const
{
	return m_flagged;
}

void Cell::SetFlagged(bool flagged)
{
	m_flagged = flagged;
}

//////
//	END SETTERS AND GETTERS
///////////////////////////////////////////////////////////////