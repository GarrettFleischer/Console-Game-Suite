/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "FreecellMenu.h"

#include "Keyboard.h"

FreecellMenu::FreecellMenu()
	: m_mainMenu(0, CWidth() / 2, CHeight() / 4, Color::green), m_game(nullptr)
{
	Menu scenarios(0, 0, 0, Color::green);
	scenarios.AddButton(Button(0, 0, VICTORY, "Victory"));
	scenarios.AddButton(Button(0, 0, STACKS, "Stacks"));
	scenarios.AddButton(Button(0, 0, BACK_ID, "Back"));

	m_mainMenu.AddButton(Button(0, 0, PLAY, "Play"));
	m_mainMenu.AddButton(Button(0, 0, GAME, "Game"));
	m_mainMenu.AddSubmenu(Button(0, 0, SCENARIOS, "Scenarios"), scenarios);
	m_mainMenu.AddButton(Button(0, 0, EXIT, "Exit"));

	m_mainMenu.Draw();
}

FreecellMenu::FreecellMenu(const FreecellMenu & copy)
	: m_mainMenu(copy.m_mainMenu), m_game(copy.m_game)
{}

FreecellMenu::~FreecellMenu()
{}

FreecellMenu & FreecellMenu::operator=(const FreecellMenu & rhs)
{
	if (this != &rhs)
	{
		m_mainMenu = rhs.m_mainMenu;
		m_game = rhs.m_game;
	}

	return *this;
}

/************************************************************************
* Purpose: To update the menu, or the game if the user has clicked "Play"
*			or one of the scenarios
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if the game or menu is still running
*************************************************************************/
bool FreecellMenu::Update()
{
	bool running = true;

	// If there is an active game
	if (m_game)
	{
		if (!m_game->Update())
		{
			Keyboard::ClearState(); // so the esc key doesn't carry over...

			delete m_game;
			m_game = nullptr;

			m_mainMenu.Draw();
		}
	}
	// If we are on the menu
	else
	{
		m_mainMenu.Update();

		// Draw help text
		int x = 19;
		int y = CHeight() - 16;
		CWrite(x, y, "Freecell!", CMakeColor(Color::bright_white, Color::green));

		CWrite(x, y + 2, "Use the mouse to select and move stacks of cards", CMakeColor(Color::bright_white, Color::green));
		CWrite(x, y + 3, "Use Ctrl + Z to undo moves", CMakeColor(Color::bright_white, Color::green));
		CWrite(x, y + 4, "Use Ctrl + Y to redo moves", CMakeColor(Color::bright_white, Color::green));
		CWrite(x, y + 5, "Use Esc to return to menu or exit the program", CMakeColor(Color::bright_white, Color::green));

		CWrite(x, y + 7, "Use \"Victory\" scenario to test winning the game", CMakeColor(Color::bright_white, Color::green));
		CWrite(x, y + 8, "Use \"Stacks\" scenario to test moving various sized stacks around", CMakeColor(Color::bright_white, Color::green));

		CWrite(x, y + 11, "NOTE: USING THE WINDOW CLOSE BUTTON FALSELY REPORTS MEMORY LEAKS!", CMakeColor(Color::bright_white, Color::green));
		CWrite(x, y + 12, "(because the process is terminated in the middle of the game loop", CMakeColor(Color::bright_white, Color::green));
		CWrite(x + 1, y + 13, "and thus, objects do not go out of scope...)", CMakeColor(Color::bright_white, Color::green));

		// Handle which button was clicked by the user
		Button * b = m_mainMenu.Clicked(Mouse::LEFT);
		if (b)
		{
			switch (b->ID())
			{
			case PLAY:
				m_game = new Freecell;
				break;

			case GAME:
				CWrite(x, y - 5, "TODO: allow the user to input the game number they wish to play", CMakeColor(Color::bright_white, Color::green));
				break;

			case VICTORY:
				m_game = new Freecell(FCBoard::VICTORY);
				break;

			case STACKS:
				m_game = new Freecell(FCBoard::STACKS);
				break;

			case EXIT:
				running = false;
				break;
			}
		}
	}

	return (running && !Keyboard::KeyPressed(VK_ESCAPE));
}
