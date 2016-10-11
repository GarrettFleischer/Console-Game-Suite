/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Keyboard.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <Windows.h>
#include <string>
using std::string;

#include "Array.h"


/************************************************************************
* Class: Keyboard
*
* Purpose: This class provides a non-blocking interface between the keyboard
*			and the Windows console
*
* Manager functions:
*	N/A
*
* Methods:
*	Public:
*		UpdateKeyboardState()
*			To be called before any other methods
*
*		KeyUp(int key)
*
*		KeyDown(int key)
*
*		KeyPressed(int key)
*
*		KeyReleased(int key)
*
*		String()
*			Returns a string representation of the user input if StoreInput is enabled
*
*		SetStoreInput(bool store_input)
*			Toggle whether or not user input is stored in String()
*			By default, the keyboard does not store input
*
*		CapsLock()
*			Returns whether or not Caps Lock is turned on
*
*	Private:
*		UpdateString()
*
*************************************************************************/
class Keyboard
{
public:
	// METHODS
	static void UpdateKeyboardState();

	static void ClearState();

	static bool KeyUp(int key);

	static bool KeyDown(int key);

	static bool KeyPressed(int key);

	static bool KeyReleased(int key);

	// GETTERS AND SETTERS
	static string & String();

	static void SetStoreInput(bool store_input);

	bool CapsLock();

private:
	// METHODS
	static void UpdateString();

	// MEMBERS
	static const int NUM_KEYS = 128; // 256
	static Array<int> m_previous_state;
	static Array<int> m_current_state;

	static bool m_storeInput;
	static string m_string;

	static bool m_capsLock;
};


#endif // KEYBOARD_H