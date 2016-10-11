/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "HistoryManager.h"

///////////////////////////////////////////////////////////////
//	INITIALIZE SINGLETON
//////

HistoryManager HistoryManager::m_instance = HistoryManager();

//////
//	END INITIALIZE SINGLETON
///////////////////////////////////////////////////////////////

HistoryManager::HistoryManager()
	: m_undid(false), m_redid(false), m_pollEvents(true)
{}

// private passthrough to prevent usage
HistoryManager::HistoryManager(const HistoryManager & copy)
	: m_undos(copy.m_undos), m_redos(copy.m_redos), m_undid(copy.m_undid), m_redid(copy.m_redid), m_pollEvents(copy.m_pollEvents)
{}

HistoryManager::~HistoryManager()
{
	while (!m_undos.isEmpty())
		delete m_undos.Pop();

	while (!m_redos.isEmpty())
		delete m_redos.Pop();
}

// private passthrough to prevent usage
HistoryManager & HistoryManager::operator=(const HistoryManager & rhs)
{
	return *this;
}

void HistoryManager::AddAction(HistoryAction * undo)
{
	// Clean out redo cache
	while (!m_instance.m_redos.isEmpty())
		delete m_instance.m_redos.Pop();

	m_instance.m_undos.Push(undo);
}

void HistoryManager::RemoveActions(void * me)
{
	LStack<HistoryAction *> temp;

	while (!m_instance.m_undos.isEmpty())
		temp.Push(m_instance.m_undos.Pop());

	while (!temp.isEmpty())
	{
		if (temp.Peek()->Contains(me))
			delete temp.Pop();
		else
			m_instance.m_undos.Push(temp.Pop());
	}

	while (!m_instance.m_redos.isEmpty())
		temp.Push(m_instance.m_redos.Pop());

	while (!temp.isEmpty())
	{
		if (temp.Peek()->Contains(me))
			delete temp.Pop();
		else
			m_instance.m_redos.Push(temp.Pop());
	}
}

void HistoryManager::Undo()
{
	if (!m_instance.m_undos.isEmpty())
	{
		HistoryAction * action = m_instance.m_undos.Pop();
		action->Undo();

		m_instance.m_redos.Push(action);
		m_instance.m_undid = true;
	}
}

void HistoryManager::Redo()
{
	if (!m_instance.m_redos.isEmpty())
	{
		HistoryAction * action = m_instance.m_redos.Pop();
		action->Redo();

		m_instance.m_undos.Push(action);
		m_instance.m_redid = true;
	}
}

void HistoryManager::Update()
{
	m_instance.m_undid = false;
	m_instance.m_redid = false;

	if(m_instance.m_pollEvents)
	{
		if (Keyboard::KeyDown(VK_CONTROL))
		{
			if (Keyboard::KeyPressed('Z'))
				Undo();
			else if (Keyboard::KeyPressed('Y'))
				Redo();
		}
	}
}

void HistoryManager::ClearCache()
{
	while (!m_instance.m_undos.isEmpty())
		delete m_instance.m_undos.Pop();

	while (!m_instance.m_redos.isEmpty())
		delete m_instance.m_redos.Pop();
}

bool HistoryManager::DidUndo()
{
	return m_instance.m_undid;
}

bool HistoryManager::DidRedo()
{
	return m_instance.m_redid;
}

bool HistoryManager::DidChange()
{
	return (DidUndo() || DidChange());
}

void HistoryManager::PollEvents(bool poll)
{
	m_instance.m_pollEvents = poll;
}
