/************************************************************************
* Author:		Garrett Fleischer
* Filename:		doublelinkedlist.h
* Date Created:	1/6/16
* Modifications:
*	N/A
*************************************************************************/

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "ListNode.h"
#include "Exception.h"

/************************************************************************
* Class: DoubleLinkedList
*
* Purpose: A Memory Efficient Data Structure
*
* Manager functions:
* 	DoubleLinkedList ( )
* 		The default head and tail values are nullptr
*
*	DoubleLinkedList (const DoubleLinkedList & copy)
*	operator = (const DoubleLinkedList & rhs)
*
*	~ListNode()
*
* Methods:
*	PUBLIC
*		bool isEmpty() const;
*		const T & First() const;
*		const T & Last() const;
*
*		void Prepend(const T & item);
*		void Append(const T & item);
*
*		void InsertAfter(const T & item, const T & after);
*		void InsertBefore(const T & item, const T & before);
*
*		void Extract(const T & item);
*		void Purge();
*
*	PRIVATE
*		ListNode<T> * FindNode(const T & data);
*		static void DeepCopyNodes(DoubleLinkedList * dest, const DoubleLinkedList * source);
*
*************************************************************************/
template<typename T>
class DoubleLinkedList
{
	template<typename IT>
	friend class ListIterator;

public:
    // C'TORS & D'TOR
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList & copy);
    
    ~DoubleLinkedList();
   
    // OPERATORS
    DoubleLinkedList<T> & operator=(const DoubleLinkedList & rhs);
    
    // METHODS
	bool Size() const;
    bool isEmpty() const;
    T & First();
	const T & First() const;
	T & Last();
	const T & Last() const;
    
    void Prepend(const T & item);
    void Append(const T & item);
    
	void InsertBefore(const T & item, const T & before);
    void InsertAfter(const T & item, const T & after);
    
    void Purge();
    void Extract(const T & item);
    
private:
    // METHODS
    ListNode<T> * FindNode(const T & data);
    static void DeepCopyNodes(DoubleLinkedList * dest, const DoubleLinkedList * source);
    
    // MEMBERS
    ListNode<T> * m_head;
    ListNode<T> * m_tail;
	int m_size;
};



///////////////////////////////////////////////////////////////
// C'TORS & D'TOR
//////

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
	: m_head(nullptr), m_tail(nullptr), m_size(0)
{}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList & copy)
    : m_head(nullptr), m_tail(nullptr), m_size(copy.m_size)
{
    DeepCopyNodes(this, &copy);
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    Purge();
}

//////
// END C'TORS & D'TOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// OPERATORS
//////

/************************************************************************
* Purpose: To perform a deep copy of rhs's data to this list
*
* Precondition:
*		N/A
*
* Postcondition:
*		Modifies:	Purges all data in this list before copying
*		Throws:		N/A
*		Returns:	The updated list
*************************************************************************/
template<typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList & rhs)
{
	m_size = rhs.m_size;

    if(this != &rhs)
        DeepCopyNodes(this, &rhs);

	return *this;
}

//////
// END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////


template<typename T>
bool DoubleLinkedList<T>::Size() const
{
	return m_size;
}

template<typename T>
bool DoubleLinkedList<T>::isEmpty() const
{
    return (m_size == 0);
}


/************************************************************************
* Purpose: To access the first data value in the list
*
* Precondition:
*		The list may NOT be empty
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	"Cannot access first element: LIST_IS_EMPTY"
*		Returns:	A const reference to the first data value
*************************************************************************/
template<typename T>
T & DoubleLinkedList<T>::First()
{
    if(m_head == nullptr)
        throw Exception("Cannot access first element: LIST_IS_EMPTY");
    
    return m_head->Data();
}

template<typename T>
const T & DoubleLinkedList<T>::First() const
{
	if (m_head == nullptr)
		throw Exception("Cannot access first element: LIST_IS_EMPTY");

	return m_head->Data();
}

/************************************************************************
* Purpose: To access the last data value in the list
*
* Precondition:
*		The list may NOT be empty
*
* Postcondition:
*		Modifies:	N/A
*		Throws:	"Cannot access last element: LIST_IS_EMPTY"
*		Returns:	A const reference to the last data value
*************************************************************************/
template<typename T>
T & DoubleLinkedList<T>::Last()
{
    if(m_head == nullptr)
        throw Exception("Cannot access last element: LIST_IS_EMPTY");
    
    return m_tail->Data();
}

template<typename T>
const T & DoubleLinkedList<T>::Last() const
{
	if (m_head == nullptr)
		throw Exception("Cannot access last element: LIST_IS_EMPTY");

	return m_tail->Data();
}

/************************************************************************
* Purpose: To insert an item into the beginning of the list
*
* Precondition:
*		N/A
*
* Postcondition:
*		Modifies:	The head and/or tail pointer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Prepend(const T & item)
{
    ListNode<T> * node = new ListNode<T>(item);

	if (m_head == nullptr) // empty
	{
		m_head = node;
		m_tail = node;
	}
	else
	{
		node->Next() = m_head;
		m_head->Prev() = node;
		m_head = node;
	}

	m_size++;
}

/************************************************************************
* Purpose: To add an item onto the end of the list
*
* Precondition:
*		N/A
*
* Postcondition:
*		Modifies:	The tail and/or head pointer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Append(const T & item)
{
    ListNode<T> * node = new ListNode<T>(item);
    
    if(m_head == nullptr) // list is empty
    {
        m_head = node;
		m_tail = node;
    }
    else
    {
        node->Prev() = m_tail;
        m_tail->Next() = node;
        m_tail = node;
    }
    
	m_size++;
}


/************************************************************************
* Purpose: To insert a new item before a matching item in the list
*
* Precondition:
*		before - must have a matching item in the list
*
* Postcondition:
*		Modifies:	The head pointer
*		Throws:	"Item to insert before not found!"
*		Returns:	N/A
*************************************************************************/
template<typename T>
void DoubleLinkedList<T>::InsertBefore(const T & item, const T & before)
{
    ListNode<T> * found_node = FindNode(before);
    
    if(found_node == nullptr)
    {
        throw Exception("Item to insert before not found!");
    }
    else
    {
        ListNode<T> * node = new ListNode<T>(item);
        
		if (found_node == m_head)
			m_head = node;
        else
            found_node->Prev()->Next() = node;
         
        node->Prev() = found_node->Prev();
        node->Next() = found_node;
        found_node->Prev() = node;

		m_size++;
    }
}

/************************************************************************
* Purpose: To insert a new item after a matching item in the list
*
* Precondition:
*		after - must have a matching item in the list
*
* Postcondition:
*		Modifies:	The tail pointer
*		Throws:	"Item to insert after not found!"
*		Returns:	N/A
*************************************************************************/
template<typename T>
void DoubleLinkedList<T>::InsertAfter(const T & item, const T & after)
{
    ListNode<T> * found_node = FindNode(after);
    
    if(found_node == nullptr)
    {
        throw Exception("Item to insert after not found!");
    }
    else
    {
        ListNode<T> * node = new ListNode<T>(item);
        
        if((found_node == m_tail))
            m_tail = node;
        else
            found_node->Next()->Prev() = node;
        
        node->Prev() = found_node;
        node->Next() = found_node->Next();
        found_node->Next() = node;

		m_size++;
    }
}


/************************************************************************
* Purpose: To return the list to its default state
*
* Precondition:
*		N/A
*
* Postcondition:
*		Modifies:	The head and tail pointers
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Purge()
{
    ListNode<T> * travel = m_head;
    ListNode<T> * trail = nullptr;
    
    while(travel)
    {
        trail = travel;
        travel = travel->Next();
        
        delete trail;
    }

	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

/************************************************************************
* Purpose: To delete a matching item in the list
*
* Precondition:
*		item - must have a matching item in the list
*
* Postcondition:
*		Modifies:	Nodes in the list
*		Throws:	"Item to extract not found!"
*		Returns:	N/A
*************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Extract(const T & item)
{
    ListNode<T> * found_node = FindNode(item);
    
    if(found_node == nullptr)
    {
        throw Exception("Item to extract not found!");
    }
    else
    {
		if (m_head == m_tail)
		{
			m_head = nullptr;
			m_tail = nullptr;
		}
        else if(found_node == m_head)
        {
            m_head = m_head->Next();
			if (m_head)
				m_head->Prev() = nullptr;
        }
        else if(found_node == m_tail)
        {
            m_tail = m_tail->Prev();
			if (m_tail)
				m_tail->Next() = nullptr;
        }
        else
        {
            found_node->Next()->Prev() = found_node->Prev();
            found_node->Prev()->Next() = found_node->Next();
        }
        
        delete found_node;
		m_size--;
    }
}

//////
// END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// PRIVATE METHODS
//////


/************************************************************************
* Purpose: To find a node that contains matching data
*
* Precondition:
*		N/A
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The matching node OR nullptr if not found
*************************************************************************/
template<typename T>
ListNode<T> * DoubleLinkedList<T>::FindNode(const T & data)
{
    bool found = false;
    ListNode<T> * travel = m_head;
    
    while(travel && !found)
    {
        if(travel->Data() == data)
            found = true;
        else
            travel = travel->Next();
    }
    
    return travel;
}


/************************************************************************
* Purpose: To deep copy all data from source into dest
*
* Precondition:
*		dest & source - must exist
*
* Postcondition:
*		Modifies:	Purges dest before copying data into it
*		Throws:	"Destination DoubleLinkedList does not exist!"
*				"Source DoubleLinkedList does not exist!"
*		Returns:	N/A
*************************************************************************/
template<typename T>
void DoubleLinkedList<T>::DeepCopyNodes(DoubleLinkedList * dest, const DoubleLinkedList * source)
{
	if (!dest)
		throw "Destination DoubleLinkedList does not exist!";
	else if (!source)
		throw "Source DoubleLinkedList does not exist!";

    ListNode<T> * travel_copy = source->m_head;
	dest->Purge();
    
    while(travel_copy)
    {
		dest->Append(travel_copy->Data());
        travel_copy = travel_copy->Next();
    }
}

//////
// END PRIVATE METHODS
///////////////////////////////////////////////////////////////



#endif // DOUBLELINKEDLIST_H



