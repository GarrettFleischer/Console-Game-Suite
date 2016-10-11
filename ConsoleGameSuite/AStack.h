/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Stack.h
* Date Created:	1/29/16
* Modifications:
*
*************************************************************************/

#ifndef ASTACK_H
#define ASTACK_H

#include "Array.h"
#include "Exception.h"


/************************************************************************
* Class: Stack
*
* Purpose: This class uses an Array to store data in a FILO structure
*
* Manager functions:
* 	Stack ( )
* 		The default size is zero.
*
*	Stack (const Stack & copy)
*	operator = (const Stack & rhs)
*
*	~Stack()
*
* Methods:
*
*	Push(T item)	: void
*
*	Pop()			: T
*
*	Peek()			: T
*
*	Size()			: int
*
*	MaxSize()		: int
*
*	isEmpty()		: bool
*
*	isFull()		: bool
*
*************************************************************************/
template<typename T>
class AStack
{
public:
	// CTORS AND DTOR
	AStack(int size = 0);
	AStack(const AStack & copy);

	~AStack();

	// OPERATORS
	AStack & operator=(const AStack & rhs);

	int Size() const;
	int MaxSize() const;
	bool isEmpty() const;
	bool isFull() const;

	void Push(T item);
	T Pop();
	T & Peek();
	const T & Peek() const;

	void Resize(int size);

private:
	// MEMBERS
	Array<T> m_array;
	int m_size;

};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

/************************************************************************
* Purpose: To initialize a stack with a given size
*
* Precondition:
*		size - must be non-negative
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Cannot initialize Stack with size less than zero!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
AStack<T>::AStack(int size)
	: m_size(0)
{
	if (size < 0)
		throw Exception("Cannot initialize Stack with size less than zero!");

	m_array = Array<T>(size);
}

template<typename T>
AStack<T>::AStack(const AStack & copy)
	: m_array(copy.m_array), m_size(copy.m_size)
{}

template<typename T>
AStack<T>::~AStack()
{
	m_array.Purge();
	m_size = 0;
}


//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

template<typename T>
AStack<T> & AStack<T>::operator=(const AStack & rhs)
{
	if (this != &rhs)
	{
		m_array = rhs.m_array;
		m_size = rhs.m_size;
	}

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS
//////

/************************************************************************
* Purpose: To get the current number of items on the stack
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current number of items on the stack
*************************************************************************/
template<typename T>
int AStack<T>::Size() const
{
	return m_size;
}

/************************************************************************
* Purpose: To get the maximum number of items the stack can hold
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The the maximum number of items the stack can hold
*************************************************************************/
template<typename T>
int AStack<T>::MaxSize() const
{
	return m_array.Length();
}

/************************************************************************
* Purpose: To check if there are no items on the stack
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the stack is empty
*************************************************************************/
template<typename T>
bool AStack<T>::isEmpty() const
{
	return m_size <= 0;
}

/************************************************************************
* Purpose: To check if the number of items on the stack meets or exceeds
			the maximum number of items the stack can hold
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the stack is full
*************************************************************************/
template<typename T>
bool AStack<T>::isFull() const
{
	return m_size >= m_array.Length();
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: To push a new item on top of the stack
*
* Precondition:
*		The stack cannot be full
*
* Postcondition:
*		Modifies:	The stack itself, and the number of items on the stack
*		Throws:	Exception("Stack Overflow!");
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AStack<T>::Push(T item)
{
	if (isFull())
		throw Exception("Stack Overflow!");

	m_array[m_size++] = item;
}

/************************************************************************
* Purpose: To remove an item off the top of the stack and return it
*
* Precondition:
*		The stack cannot be empty
*
* Postcondition:
*		Modifies:	The stack itself, and the number of items on the stack
*		Throws:	Exception("Stack Underflow!")
*		Returns:	The item that was removed from the top of the stack by value
*************************************************************************/
template<typename T>
T AStack<T>::Pop()
{
	if(isEmpty())
		throw Exception("Stack Underflow!");

	return m_array[--m_size];
}

/************************************************************************
* Purpose: To look at the item on the top of the stack
*
* Precondition:
*		The stack cannot be empty
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Stack Underflow!")
*		Returns:	The item on top of the stack by reference
*************************************************************************/
template<typename T>
T & AStack<T>::Peek()
{
	if (isEmpty())
		throw Exception("Stack Underflow!");

	return m_array[m_size - 1];
}

template<typename T>
const T & AStack<T>::Peek() const
{
	if (isEmpty())
		throw Exception("Stack Underflow!");

	return m_array[m_size - 1];
}

/************************************************************************
* Purpose: To change the maximum number of items the stack can hold
*
* Precondition:
*		size - must be greater than zero
*
* Postcondition:
*		Modifies:	m_array
*		Throws:	Exception("Cannot resize Stack to a size less than zero!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void AStack<T>::Resize(int size)
{
	if (size < 0)
		throw Exception("Cannot resize Stack to a size less than zero!");

	m_array.SetLength(size);
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////


#endif // ASTACK_H
