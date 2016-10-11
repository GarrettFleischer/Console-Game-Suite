/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Exception.cpp
* Date Created:	1/5/16
* Modifications:
*	1/12/16 - Fixed default c'tor behaviour
*			- Fixed operator<< behaviour with empty message
*************************************************************************/
#include "Exception.h"

#include <cstring>


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

Exception::Exception()
	: m_message(nullptr)
{}

Exception::Exception(const char * msg)
	: m_message(nullptr)
{
	SetMessage(msg);
}

Exception::Exception(const Exception & copy)
	: m_message(nullptr)
{
	*this = copy;
}

Exception::~Exception()
{
	delete[] m_message;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

Exception & Exception::operator=(const Exception & rhs)
{
	if (this != &rhs)
		SetMessage(rhs.m_message);

	return *this;
}

ostream & operator<<(ostream & stream, const Exception & excep)
{
	return (stream << ((excep.m_message) ? excep.m_message : ""));
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS & SETTERS
//////

const char * Exception::Message() const
{
	return m_message;
}

void Exception::SetMessage(const char * msg)
{
	delete[] m_message;
	m_message = new char[strlen(msg) + 1];
	strcpy(m_message, msg);
}

//////
//	END GETTERS & SETTERS
///////////////////////////////////////////////////////////////