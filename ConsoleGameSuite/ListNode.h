/************************************************************************
* Author:		Garrett Fleischer
* Filename:		listnode.h
* Date Created:	1/6/16
* Modifications:
*	N/A
*************************************************************************/

#ifndef LISTNODE_H
#define LISTNODE_H


/************************************************************************
* Class: ListNode
*
* Purpose: Necessary for DoubleLinkedList to function
*
* Manager functions:
* 	ListNode ( )
* 		The default next and prev values are nullptr
*
*	ListNode (const T & data)
*		Convenience C'tor for initializing with data
*
*	ListNode (const ListNode & copy)
*	operator = (const ListNode & rhs)
*
*	~ListNode()
*
* Methods:
*	PUBLIC
*		T & Data();
*		void SetData(const T & data);
*
*	PRIVATE
*		ListNode<T> *& Prev();
*		ListNode<T> *& Next();
*
*************************************************************************/
template<typename T>
class ListNode
{ 
    template<typename DT>
    friend class DoubleLinkedList;

	template<typename IT>
	friend class ListIterator;

public:
    // METHODS
    T & Data();
	void SetData(const T & data);
    
private:
    // C'TORS & D'TOR
    ListNode();
    ListNode(const T & data);
    ListNode(const ListNode & copy);
    
    ~ListNode();
    
    // OPERATORS
    ListNode<T> & operator=(const ListNode & rhs);
    
    // METHODS
	ListNode<T> *& Prev();
	ListNode<T> *& Next();
    
    // MEMBERS
    T m_data;
    ListNode<T> * m_prev;
    ListNode<T> * m_next;
};


///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
ListNode<T>::ListNode()
    : m_prev(nullptr), m_next(nullptr)
{}

template<typename T>
ListNode<T>::ListNode(const T & data)
    : m_data(data), m_prev(nullptr), m_next(nullptr)
{}

template<typename T>
ListNode<T>::ListNode(const ListNode & copy)
    : m_data(copy.Data()), m_prev(copy.Prev()), m_next(copy.Next())
{}

template<typename T>
ListNode<T>::~ListNode()
{
	m_prev = nullptr;
	m_next = nullptr;
}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

template<typename T>
ListNode<T> & ListNode<T>::operator=(const ListNode & rhs)
{
    m_data = rhs.Data();
    m_prev = rhs.Prev();
    m_next = rhs.Next();
}

//////
// END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////

template<typename T>
T & ListNode<T>::Data()
{
    return m_data;
}

template<typename T>
void ListNode<T>::SetData(const T & data)
{
	m_data = data;
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PRIVATE METHODS
//////

template<typename T>
ListNode<T> *& ListNode<T>::Prev()
{
	return m_prev;
}

template<typename T>
ListNode<T> *& ListNode<T>::Next()
{
	return m_next;
}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////

#endif // LISTNODE_H

