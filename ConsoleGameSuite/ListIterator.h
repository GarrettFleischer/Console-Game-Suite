#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "DoubleLinkedList.h"
#include "Iterator.h"

template<typename T>
class ListIterator : public Iterator<T>
{
public:
	ListIterator(DoubleLinkedList<T> * list);
	~ListIterator();

	virtual void First();

	virtual void MoveNext();

	virtual T & GetCurrent();

	virtual bool IsDone();

private:
	DoubleLinkedList<T> * m_list;
	ListNode<T> * m_current;
};

template<typename T>
ListIterator<T>::ListIterator(DoubleLinkedList<T> * list)
	: m_list(list), m_current(list->m_head)
{}

template<typename T>
ListIterator<T>::~ListIterator()
{}

template<typename T>
void ListIterator<T>::First()
{
	m_current = m_list->m_head;
}

template<typename T>
void ListIterator<T>::MoveNext()
{
	m_current = m_current->Next();
}

template<typename T>
T & ListIterator<T>::GetCurrent()
{
	return m_current->Data();
}

template<typename T>
bool ListIterator<T>::IsDone()
{
	return m_current == nullptr;
}

#endif // LISTITERATOR_H

