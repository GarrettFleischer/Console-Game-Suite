/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Keyboard.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#include "Keyboard.h"


///////////////////////////////////////////////////////////////
//	INITIALIZE STATIC VARS
//////

Array<int> Keyboard::m_previous_state = Array<int>(NUM_KEYS);
Array<int> Keyboard::m_current_state = Array<int>(NUM_KEYS);

bool Keyboard::m_storeInput = false;
string Keyboard::m_string = "";
bool Keyboard::m_capsLock = false;

//////
//	END INITIALIZE STATIC VARS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC STATIC METHODS
//////

/************************************************************************
* Purpose: To update the current state of the keyboard keys
*			and the string of user input if StoreInput is enabled
*
* Precondition:
*
* Postcondition:
*		Modifies:	The current and previous state of the keyboard keys
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Keyboard::UpdateKeyboardState()
{
	m_capsLock = ((GetKeyState(VK_CAPITAL) & 0x0001) == 1);

	m_previous_state = m_current_state;
	for (UINT i = 0; i < NUM_KEYS; ++i)
		m_current_state[i] = GetAsyncKeyState(i);

	if (m_storeInput)
		UpdateString();
}

void Keyboard::ClearState()
{
	m_previous_state = Array<int>(NUM_KEYS);
	m_current_state = Array<int>(NUM_KEYS);
}


/************************************************************************
* Purpose: To check if the given key is not pressed
*
* Precondition:
*		key - the keyboard key to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given key is not pressed
*************************************************************************/
bool Keyboard::KeyUp(int key)
{
	return (m_current_state[key] == 0);
}

/************************************************************************
* Purpose: To check if the given key is held down
*
* Precondition:
*		key - the keyboard key to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given key is held down
*************************************************************************/
bool Keyboard::KeyDown(int key)
{
	return (m_previous_state[key] != 0 && m_current_state[key] != 0);
}

/************************************************************************
* Purpose: To check if the given key was just pressed
*
* Precondition:
*		key - the keyboard key to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given key was just pressed
*************************************************************************/
bool Keyboard::KeyPressed(int key)
{
	return (!m_previous_state[key] && m_current_state[key]);
}

/************************************************************************
* Purpose: To check if the given key was just released
*
* Precondition:
*		key - the keyboard key to check against
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the given key was just released
*************************************************************************/
bool Keyboard::KeyReleased(int key)
{
	return (m_previous_state[key] && !m_current_state[key]);
}

//////
//	END PUBLIC STATIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS AND SETTERS
//////

/************************************************************************
* Purpose: To get a string of the user input
*
* Precondition:
*		RecordInput must be enabled for the string to update
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	A string of the user input
*************************************************************************/
string & Keyboard::String()
{
	return m_string;
}

/************************************************************************
* Purpose: To set whether or not key strokes should be recorded in String()
*
* Precondition:
*
* Postcondition:
*		Modifies:	Storage of user input
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Keyboard::SetStoreInput(bool store_input)
{
	m_storeInput = store_input;
}

/************************************************************************
* Purpose: To get the state of the Caps Lock key
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	Whether or not Caps Lock is on
*************************************************************************/
bool Keyboard::CapsLock()
{
	return m_capsLock;
}

//////
//	END GETTERS AND SETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE STATIC METHODS
//////

/************************************************************************
* Purpose: To record the user input typed into the console
*
*	TODO: UPDATE TO INCLUDE ALL VISIBLE CHARACTERS
*
* Precondition:
*
* Postcondition:
*		Modifies:	The string containing the user's key strokes
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Keyboard::UpdateString()
{
	if (KeyPressed(VK_BACK))
	{
		int new_len = m_string.length() - 1;
		if (new_len > 0)
		{
			char * str = new char[new_len + 1];
			for (int i = 0; i < new_len; ++i)
				str[i] = m_string[i];

			str[new_len] = '\0';

			m_string = string(str);
			delete[] str;
		}
		else
			m_string = string();
	}
	else if (KeyPressed(VK_SPACE))
	{
		m_string += ' ';
	}
	else
	{
		bool caps = (m_capsLock && !m_current_state[VK_SHIFT]) ||
					(m_current_state[VK_SHIFT] && !m_capsLock);

		// LETTERS
		for (UINT i = 'A'; i <= 'Z'; ++i)
		{
			if (KeyPressed(i))
				m_string += char(i + ((!caps) * 32));
		}

		// NUMBERS
		if (!m_current_state[VK_SHIFT])
		{
			for (UINT i = '0'; i <= '9'; ++i)
			{
				if (KeyPressed(i))
					m_string += char(i);
			}
		}
		// SPECIALS
		else
		{
			if (KeyPressed('1'))
				m_string += '!';

			if (KeyPressed('2'))
				m_string += '@';

			if (KeyPressed('3'))
				m_string += '#';

			if (KeyPressed('4'))
				m_string += '$';

			if (KeyPressed('5'))
				m_string += '%';

			if (KeyPressed('6'))
				m_string += '^';

			if (KeyPressed('7'))
				m_string += '&';

			if (KeyPressed('8'))
				m_string += '*';

			if (KeyPressed('9'))
				m_string += '(';

			if (KeyPressed('0'))
				m_string += ')';
		}
	}
}

//////
//	END PRIVATE STATIC METHODS
///////////////////////////////////////////////////////////////