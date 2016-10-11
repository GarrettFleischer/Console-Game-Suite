/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		Main.cpp
Date Created:	1/12/16
Modifications:
		1/27/16 - FIXED NARROWING CONVERSION ERRORS IN VS 2015+
		2/2/16 - Updated main to use improved console drawing.
		2/8/16 - Updated to display the Freecell game rather than Minesweeper

		TODO: CREATE GAMESUITE MANAGER FOR PICKING WHICH GAME TO PLAY

Lab/Assignment: L1

Overview: Suite of games for the console:
			Minesweeper
			Freecell

Input: Input is received in a non-blocking manner from the mouse and keyboard

Output: The output for this program is to the console window and consists of clickable
		buttons and tiles.

*****************************************************************************************/

#include <iostream>
using std::cout;
using std::endl;

#include "crtdbg_new.h"

#include "MineSweeper.h"
#include "Console.h"
#include "HistoryManager.h"

#include "Freecell.h"
#include "FreecellMenu.h"

const float FRAMES = 250;
const float SECOND = std::milli::den;
const float FPS = (SECOND / FRAMES);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FreecellMenu menu;

	bool running(true);

	while (running)
	{
		if (CDeltaTime() > FPS)
		{
			Mouse::UpdateMouseState();
			Keyboard::UpdateKeyboardState();
			HistoryManager::Update();

			running = menu.Update();

			CUpdate();
		}
	}

	/*MineSweeper minesweeper;

	bool running = true;
	while (running && !Keyboard::KeyPressed(VK_ESCAPE))
	{
		Mouse::UpdateMouseState();
		Keyboard::UpdateKeyboardState();

		running = minesweeper.Update();

		HistoryManager::Update();
		CUpdate();
	}*/

	return 0;
}
