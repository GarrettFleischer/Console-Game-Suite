/************************************************************************
* Author:		Garrett Fleischer
* Filename:		HistoryAction.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef UNDO_H
#define UNDO_H

/************************************************************************
* Class: HistoryAction
*
* Purpose: This class is an interface for Undo and Redo actions
*
* Manager functions:
*	HistoryAction();
*	HistoryAction(const HistoryAction & copy);
*	~HistoryAction()
*	HistoryAction & operator=(const HistoryAction & rhs);
*
* Methods:
*
*************************************************************************/
class HistoryAction
{
	friend class HistoryManager;

protected:
	virtual void Undo() = 0;
	virtual void Redo() = 0;

	virtual bool Contains(void * item) = 0;
};

#endif // UNDO_H
