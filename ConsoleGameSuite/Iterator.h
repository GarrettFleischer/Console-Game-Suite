#ifndef ITERATOR_H
#define ITERATOR_H

/************************************************************************
* Class: Iterator<T>
*
* Purpose: This class acts as an interface for all types of Iterator
*
* Manager functions:
*	N/A
*
* Methods:
*	Public:
*		First()		 : void
*		MoveNext()	 : void
*		GetCurrent() : T *
*		IsDone()	 : bool
*	Private:
*		N/A
*************************************************************************/
template<typename T>
class Iterator
{
public:
	virtual void First() = 0;
	virtual void MoveNext() = 0;
	virtual T & GetCurrent() = 0;
	virtual bool IsDone() = 0;
};


#endif // ITERATOR_H
