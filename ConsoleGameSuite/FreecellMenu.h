/************************************************************************
* Author:		Garrett Fleischer
* Filename:		FreecellMenu.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef FREECELLMENU_H
#define FREECELLMENU_H

#include "Menu.h"
#include "Freecell.h"


/************************************************************************
* Class: FreecellMenu
*
* Purpose: This class creates and displays the menu for the Freecell game
*			It is also responsible for updating the game once the user
*			clicks "Play" or one of the scenarios
*
* Manager functions:
*	FreecellMenu();
*	FreecellMenu(const FreecellMenu & copy);
*	~FreecellMenu()
*	FreecellMenu & operator=(const FreecellMenu & rhs);
*
* Methods:
*
*************************************************************************/
class FreecellMenu
{
public:
	enum BUTTON { PLAY, GAME, SCENARIOS, EXIT, VICTORY, STACKS, };
	FreecellMenu();
	FreecellMenu(const FreecellMenu & copy);

	~FreecellMenu();

	FreecellMenu & operator=(const FreecellMenu & rhs);

	bool Update();

private:
	Menu m_mainMenu;
	Freecell * m_game;
};

#endif // FREECELLMENU_H
