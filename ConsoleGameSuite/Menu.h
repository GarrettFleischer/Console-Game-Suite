/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Menu.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef MENU_H
#define MENU_H

#include <string>
using std::string;

#include "Array.h"
#include "Button.h"
#include "Console.h"

// Id to be assigned to all "Back" buttons
#define BACK_ID -999999

/************************************************************************
* Class: Menu
*
* Purpose: This class represents a Menu system with buttons, and buttons that lead to sub-menus.
*			Currently sub-menus must manually add a "Back" button with id = BACK_ID
*
* Manager functions:
*	Menu();
*	Menu(const Menu & copy);
*	~Menu()
*	Menu & operator=(const Menu & rhs);
*
* Methods:
*
*************************************************************************/
class Menu
{
public:
	Menu(int id = 0, int x = 0, int y = 0, COLOR background = Color::black);
	Menu(const Menu & copy);

	~Menu();

	Menu & operator=(const Menu & rhs);

	void AddButton(Button button);
	void AddSubmenu(Button button, Menu sub);

	void SetPos(int x, int y);

	Button * Clicked(Mouse::BUTTON btn);

	void Update();
	void Draw();

private:
	void ResizeButtons();

	Array<Button> m_buttons;
	Array<Menu> m_submenus;

	Menu * m_current;
	Menu * m_previous;

	COLOR m_background;

	int m_id;
	int m_x;
	int m_y;
};

#endif // MENU_H
