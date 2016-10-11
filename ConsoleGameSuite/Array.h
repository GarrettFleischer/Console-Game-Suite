/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Array.h
* Date Created:	1/4/16
* Modifications:
*	1/9/16  - Fixed out of bounds error in SetLength()
*	1/12/16 - Added Exception for initializing and setting a negative length
*			- Fixed behavior when setting length to zero
*	1/16/16 - Added Swap and Purge methods
*************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include "Exception.h"

#define MIN(arg1, arg2) ((arg1 <= arg2) ? arg1 : arg2)

/************************************************************************
* Class: Array
*
* Purpose: This class creates a dynamic one-dimensional array that can be
* started at any base.
*
* Manager functions:
* 	Array ( )
* 		The default size is zero and the base is zero.
*
*	Array (int length, int start_index = 0)
*		Creates an appropriate sized array with the starting index
*       either zero or the supplied starting value.
*
*	Array (const Array & copy)
*	operator = (const Array & copy)
*
*	~Array()
*
* Methods:
*	operator [ ] (int index)
*		Returns the value located at index in the Array
*
*************************************************************************/
template<typename T>
class Array
{
public:
	// CTOR'S & D'TOR
	Array(int length = 0, int start_index = 0);
	Array(const Array & copy);
	~Array();

	// OPERATORS
	Array<T> & operator=(const Array & rhs);
	T & operator[](int index);
	const T & operator[](int index) const;

	// GETTERS & SETTERS
	int StartIndex() const;
	void SetStartIndex(int index);

	int Length() const;
	void SetLength(int length);

	void Swap(Array<T> & other);
	void Purge();

private:
	// MEMBERS
	T * m_array;
	int m_length;
	int m_startIndex;
};


///////////////////////////////////////////////////////////////
//	C'TORS & D'TOR
//////

/************************************************************************
* Purpose: To initialize an array with a length and start index
*
* Precondition:
*		length - must be non-negative
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Error: Cannot set length to a negative value!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
Array<T>::Array(int length, int start_index)
	: m_array(nullptr), m_length(length), m_startIndex(start_index)
{
	if (m_length < 0)
		throw Exception("Error: Cannot set length to a negative value!");

	if (m_length > 0)
		m_array = new T[m_length];
}

template<typename T>
Array<T>::Array(const Array & copy)
	: m_array(nullptr), m_length(0), m_startIndex(0)
{
	*this = copy;
}

template<typename T>
Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_startIndex = 0;
}

//////
//	END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

/************************************************************************
* Purpose: To deep copy another array into this array
*
* Precondition:
*		rhs - should not be the same instance as this
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	this array after it has been modified
*************************************************************************/
template<typename T>
Array<T> & Array<T>::operator=(const Array & rhs)
{
	if (this != &rhs)
	{
		m_startIndex = rhs.StartIndex();
		m_length = rhs.Length();

		delete[] m_array;
		m_array = new T[m_length];

		size_t size = MIN(Length(), rhs.Length());
		for (size_t i = 0; i < size; ++i)
			m_array[i] = rhs.m_array[i];
	}

	return *this;
}

/************************************************************************
* Purpose: To easily access or modify values stored in the Array
*
* Precondition:
*		index - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Index out of bounds!")
*		Returns:	the value located at index
*************************************************************************/
template<typename T>
T & Array<T>::operator[](int index)
{
	int delta = (index - m_startIndex);

	if ((delta < 0) || (delta >= m_length))
		throw Exception("Array index out of bounds!");

	return m_array[delta];
}

/************************************************************************
* Purpose: To easily access values stored in the Array
*
* Precondition:
*		index - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Index out of bounds!")
*		Returns:	the value located at index
*************************************************************************/
template<typename T>
const T & Array<T>::operator[](int index) const
{
	int delta = (index - m_startIndex);

	if ((delta < 0) || (delta >= m_length))
		throw Exception("Array index out of bounds!");

	return m_array[delta];
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS & SETTERS
//////

template<typename T>
int Array<T>::StartIndex() const
{
	return m_startIndex;
}

template<typename T>
void Array<T>::SetStartIndex(int index)
{
	m_startIndex = index;
}

template<typename T>
int Array<T>::Length() const
{
	return m_length;
}

/************************************************************************
* Purpose: To change the length of the array
*
* Precondition:
*		length - must be non-negative
*
* Postcondition:
*		Modifies:	the length of the array
*		Throws:	Exception("Error: Cannot set length to a negative value!")
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Array<T>::SetLength(int length)
{
	if (length != m_length)
	{
		if (length < 0)
		{
			throw Exception("Error: Cannot set length to a negative value!");
		}
		else if (length == 0)
		{
			delete[] m_array;
			m_array = nullptr;
		}
		else
		{
			size_t min_len = MIN(m_length, length);
			T * temp = new T[length + 1];

			// copy everything up to the array with the minimum length 
			for (size_t i = 0; i < min_len; ++i)
				temp[i] = m_array[i];

			delete[] m_array;
			m_array = temp;
		}

		m_length = length;
	}
}

//////
//	END GETTERS & SETTERS
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: To swap the contents of this array and another
*
* Precondition:
*
* Postcondition:
*		Modifies:	The contents of the arrays
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Array<T>::Swap(Array<T> & other)
{
	Array<T> temp(*this);
	*this = other;
	other = temp;
}

/************************************************************************
* Purpose: To free up the memory allocated to this array
*
* Precondition:
*
* Postcondition:
*		Modifies:	The contents and length of this array
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void Array<T>::Purge()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

#endif // ARRAY_H