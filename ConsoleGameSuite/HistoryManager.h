/************************************************************************
* Author:		Garrett Fleischer
* Filename:		HistoryManager.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "LStack.h"
#include "HistoryAction.h"
#include "Keyboard.h"

/************************************************************************
* Class: HistoryManager
*
* Purpose: This class represents a Model to be connected with Views
*			When the model is updated, it Notifies all registered views
*
* Manager functions:
*	HistoryManager();
*	HistoryManager(const HistoryManager & copy);
*	~HistoryManager()
*	HistoryManager & operator=(const HistoryManager & rhs);
*
* Methods:
*
*************************************************************************/
class HistoryManager
{
public:
	// DTOR
	~HistoryManager();

	// METHODS
	static void AddAction(HistoryAction * undo);
	static void RemoveActions(void * me);

	static void Undo();
	static void Redo();

	static void Update();
	static void ClearCache();

	static bool DidUndo();
	static bool DidRedo();
	static bool DidChange();

	static void PollEvents(bool poll);

private:
	// CTORS
	HistoryManager();
	HistoryManager(const HistoryManager & copy);
	
	// OPERATOR
	HistoryManager & operator=(const HistoryManager & rhs);

	// SINGLETON INSTANCE FOR MEMORY MANAGEMENT
	static HistoryManager m_instance;

	// MEMBERS
	LStack<HistoryAction *> m_undos;
	LStack<HistoryAction *> m_redos;
	bool m_undid;
	bool m_redid;
	
	bool m_pollEvents;
};

#endif // UNDOMANAGER_H
