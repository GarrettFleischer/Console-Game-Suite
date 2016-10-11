/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Mouse.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#include "Mouse.h"


///////////////////////////////////////////////////////////////
//	INITIALIZE STATIC VARS
//////

Array<int> Mouse::m_previous_state = Array<int>(NUM_BTNS);
Array<int> Mouse::m_current_state = Array<int>(NUM_BTNS);

int Mouse::m_x = 0;
int Mouse::m_y = 0;
bool Mouse::m_moved = false;

//////
//	END INITIALIZE STATIC VARS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC STATIC METHODS
//////

/************************************************************************
* Purpose: To update the current state of the mouse buttons
*			and the location of the cursor
*
* Precondition:
*		input_handle - must be provided by console.InputHandle()
*
* Postcondition:
*		Modifies:	The current and previous state of the mouse buttons
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Mouse::UpdateMouseState()
{
	// swap the current state into the previous
	m_previous_state = m_current_state;

	// update current mouse state
	m_current_state[LEFT] = GetAsyncKeyState(VK_LBUTTON);
	m_current_state[MIDDLE] = GetAsyncKeyState(VK_MBUTTON);
	m_current_state[RIGHT] = GetAsyncKeyState(VK_RBUTTON);

	UpdatePosition();
}

/************************************************************************
* Purpose: To check if the given button is not pressed
*
* Precondition:
*		btn - the mouse button to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given button is not pressed
*************************************************************************/
bool Mouse::BtnUp(BUTTON btn)
{
	return !m_current_state[btn];
}

/************************************************************************
* Purpose: To check if the given button is held down
*
* Precondition:
*		btn - the mouse button to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given button is held down
*************************************************************************/
bool Mouse::BtnDown(BUTTON btn)
{
	return (m_previous_state[btn] != 0 && m_current_state[btn] != 0);
}

/************************************************************************
* Purpose: To check if the given button was just pressed
*
* Precondition:
*		btn - the mouse button to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given button was just pressed
*************************************************************************/
bool Mouse::BtnPressed(BUTTON btn)
{
	return (!m_previous_state[btn] && m_current_state[btn]);
}

/************************************************************************
* Purpose: To check if the given button was just released
*
* Precondition:
*		btn - the mouse button to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given button was just released
*************************************************************************/
bool Mouse::BtnReleased(BUTTON btn)
{
	return (m_previous_state[btn] && !m_current_state[btn]);
}

//////
//	END PUBLIC STATIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS
//////

/************************************************************************
* Purpose: To check if the mouse moved since the last update
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the mouse changed position since the last update
*************************************************************************/
bool Mouse::Moved()
{
	return m_moved;
}

/************************************************************************
* Purpose: To get the current x coordinate of the mouse in the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current column the mouse is in
*************************************************************************/
int Mouse::X()
{
	return m_x;
}


/************************************************************************
* Purpose: To get the current y coordinate of the mouse in the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	The current row the mouse is in
*************************************************************************/
int Mouse::Y()
{
	return m_y;
}

//////
//	END GETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE STATIC METHODS
//////

/************************************************************************
* Purpose: To update the coordinates of the mouse in the console
*
* Precondition:
*
* Postcondition:
*		Modifies:	The x and y coords as well as if the mouse moved
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Mouse::UpdatePosition()
{
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;

	GetNumberOfConsoleInputEvents(CInputHandle(), &numEvents);

	if (numEvents != 0)
	{
		// Create a buffer of that size to store the events
		INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

		// Read the console events into that buffer, and save how
		// many events have been read into numEventsRead.
		ReadConsoleInput(CInputHandle(), eventBuffer, numEvents, &numEventsRead);

		// Now, cycle through all the events that have happened:
		bool mouse_handled = false;
		for (DWORD i = 0; i < numEventsRead && !mouse_handled; ++i)
		{
			if (eventBuffer[i].EventType == MOUSE_EVENT)
			{
				// POSITION
				int old_x = m_x;
				int old_y = m_y;

				m_x = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
				m_y = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;

				m_moved = (m_x != old_x || m_y != old_y);

				mouse_handled = true;
			}
		}

		delete[] eventBuffer;
	}
}

//////
//	END PRIVATE STATIC METHODS
///////////////////////////////////////////////////////////////