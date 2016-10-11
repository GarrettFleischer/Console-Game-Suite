/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Exception.h
* Date Created:	1/5/16
* Modifications:
*	N/A
*************************************************************************/
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <ostream>
using std::ostream;


/************************************************************************
* Class: Exception
*
* Purpose: This class is used to throw a simple cstring exception
*
* Manager functions:
* 	Exception ( )
* 		The default message is an empty string.
*
*	Exception (const char * msg)
*		Copies the contents of msg into m_message
*
*	Exception (const Exception & copy)
*	operator = (const Exception & copy)
*
*	~Exception()
*
* Methods:
*	operator [ ] (int index)
*		Returns the value located at index in the Array
*
*	operator<<(std::ostream & stream, const Exception & excep)
*		Returns ostream with excep's message appended to it
*
*************************************************************************/
class Exception
{
public: 
	// C'TORS AND D'TOR
	Exception();
	Exception(const char * msg);
	Exception(const Exception & copy);
	~Exception();

	// OPERATORS
	Exception & operator=(const Exception & rhs);
	friend ostream & operator<<(ostream & stream, const Exception & excep);

	// GETTERS AND SETTERS
	const char * Message() const;
	void SetMessage(const char *msg);

private:
	// MEMBERS
	char * m_message;
};

#endif // EXCEPTION_H
