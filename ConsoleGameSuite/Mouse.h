/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Mouse.h
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef MOUSE_H
#define MOUSE_H

#include <Windows.h>
#include "Console.h"
#include "Array.h"

/************************************************************************
* Class: Mouse
*
* Purpose: This class provides a non-blocking interface between the mouse
*			and the Windows console
*
* Manager functions:
*	N/A
*
* Methods:
*	Public:
*		UpdateMouseState(HANDLE & input_handle)
*			To be called before any other methods
*	
*		BtnUp(BUTTON btn)
*
*		BtnDown(BUTTON btn)
*
*		BtnPressed(BUTTON btn)
*
*		BtnReleased(BUTTON btn)
*
*		Moved()
*
*		X()
*		Y()
*
*	Private:
*		UpdatePosition(HANDLE & input_handle)
*
*************************************************************************/
class Mouse
{
public:
	enum BUTTON { LEFT, MIDDLE, RIGHT };

	// METHODS
	static void UpdateMouseState();

	static bool BtnUp(BUTTON btn);

	static bool BtnDown(BUTTON btn);

	static bool BtnPressed(BUTTON btn);

	static bool BtnReleased(BUTTON btn);

	// GETTERS
	static bool Moved();

	static int X();
	static int Y();

private:
	// METHODS
	static void UpdatePosition();

	// MEMBERS
	static const int NUM_BTNS = 3;
	static Array<int> m_previous_state;
	static Array<int> m_current_state;

	static int m_x;
	static int m_y;
	static bool m_moved;
};


#endif // Mouse_h__
