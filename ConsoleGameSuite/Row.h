/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Row.h
* Date Created:	1/6/16
* Modifications:
*	1/12/16 - Fixed constness of operator[]
*************************************************************************/
#ifndef ROW_H
#define ROW_H

#include "Array2D.h"


/************************************************************************
* Class: Row
*
* Purpose: This class provides a way to call [][] on an Array2D
*
* Manager functions:
* 	Row (const Array2D<T> & ra, int row)
*
*	Row (const Row & copy)
*	operator = (const Row & rhs)
*
*	~Row()
*
* Methods:
*	operator [ ] (int column)
*
*************************************************************************/
template<typename T>
class Row
{
	template<typename RT>
	friend class Array2D;

public:
	// D'TOR
	~Row();

	// OPERATORS
	T & operator[](int column);
	const T & operator[](int column) const;

private:
	// C'TOR
	Row(const Array2D<T> & ra, int row);

	// MEMBERS
	Array2D<T> & m_array2D;
	int m_row;
};


/////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
Row<T>::Row(const Array2D<T> & ra, int row)
	: m_array2D(const_cast<Array2D<T> &>(ra)), m_row(row)
{}

template<typename T>
Row<T>::~Row()
{}

//////
// END C'TORS AND D'TOR
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// OPERATORS
//////

/************************************************************************
* Purpose: To easily access or modify an item in the Array
*
* Precondition:
*		column - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Column index out of bounds!")
*		Returns:	the item located at the specified row and column by reference
*************************************************************************/
template<typename T>
T & Row<T>::operator[](int column)
{
	if ((column < 0) || (column >= m_array2D.m_columns))
		throw Exception("Column index out of bounds!");

	int index = ((m_array2D.m_columns * m_row) + column);
	return m_array2D.m_array[index];
}

/************************************************************************
* Purpose: To easily access an item in a const Array
*
* Precondition:
*		column - must be within the bounds of the array
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	Exception("Column index out of bounds!")
*		Returns:	the item located at the specified row and column by const reference
*************************************************************************/
template<typename T>
const T & Row<T>::operator[](int column) const
{
	if ((column < 0) || (column >= m_array2D.m_columns))
		throw Exception("Column index out of bounds!");

	int index = ((m_array2D.m_columns * m_row) + column);
	return m_array2D.m_array[index];
}



//////
// END OPERATORS
/////////////////////////////////////////////////////////

#endif // ROW_H
