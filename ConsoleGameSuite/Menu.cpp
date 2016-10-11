/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "Menu.h"


Menu::Menu(int id, int x, int y, COLOR background)
	: m_id(id), m_x(x), m_y(y), m_background(background), m_current(this), m_previous(nullptr)
{}

Menu::Menu(const Menu & copy)
	: m_buttons(copy.m_buttons), m_submenus(copy.m_submenus), m_current(copy.m_current), m_previous(copy.m_previous),
	m_id(copy.m_id), m_x(copy.m_x), m_y(copy.m_y), m_background(copy.m_background)
{}

Menu::~Menu()
{}

Menu & Menu::operator=(const Menu & rhs)
{
	if (this != &rhs)
	{
		m_buttons = rhs.m_buttons;
		m_submenus = rhs.m_submenus;
		m_background = rhs.m_background;
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_id = rhs.m_id;
		m_previous = rhs.m_previous;
		m_current = rhs.m_current;
	}

	return *this;
}

/************************************************************************
* Purpose: Adds the given button to this menu
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Menu::AddButton(Button button)
{
	m_buttons.SetLength(m_buttons.Length() + 1);
	m_buttons[m_buttons.Length() - 1] = button;

	ResizeButtons();
	Draw();
}

/************************************************************************
* Purpose: Adds the given button to this menu and links it to the given sub-menu
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Menu::AddSubmenu(Button button, Menu sub)
{
	AddButton(button);

	sub.m_id = button.ID();
	sub.m_previous = this;
	sub.SetPos(m_x, m_y);
	m_submenus.SetLength(m_submenus.Length() + 1);
	m_submenus[m_submenus.Length() - 1] = sub;
}

/************************************************************************
* Purpose: Sets the position of this menu on the screen
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Menu::SetPos(int x, int y)
{
	for (int i = 0; i < m_buttons.Length(); ++i)
	{
		Button & b = m_buttons[i];
		b.SetPos(x - b.Width() / 2, b.Y() + (y - m_y));
	}

	m_x = x;
	m_y = y;
}


/************************************************************************
* Purpose: To return the button that was clicked in the last update
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	NULL if no button was clicked
*************************************************************************/
Button * Menu::Clicked(Mouse::BUTTON btn)
{
	Button * clicked = nullptr;
	for (int i = 0; i < m_current->m_buttons.Length(); ++i)
	{
		if (m_current->m_buttons[i].Clicked(btn))
			clicked = &(m_current->m_buttons[i]);
	}

	return clicked;
}

/************************************************************************
* Purpose: Updates the buttons of the current menu or sub-menu
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Menu::Update()
{
	if (!m_current)
		m_current = this;

	bool menu_changed = false;
	for (int i = 0; !menu_changed && i < m_current->m_buttons.Length(); ++i)
	{
		m_current->m_buttons[i].Update();

		// if the button was clicked
		if (m_current->m_buttons[i].Clicked(Mouse::LEFT))
		{
			// if it is a back button...
			if (m_current->m_buttons[i].ID() == BACK_ID)
			{
				menu_changed = true;
				m_current = m_current->m_previous;
			}
			else
			{
				// if it has a submenu attached
				for (int j = 0; !menu_changed && j < m_current->m_submenus.Length(); ++j)
				{
					if (m_current->m_submenus[j].m_id == m_current->m_buttons[i].ID())
					{
						menu_changed = true;
						m_current = &m_current->m_submenus[j];
					}
				}
			}
		}
	}

	if (!m_current)
		m_current = this;

	if (menu_changed)
		Draw();
}

/************************************************************************
* Purpose: Draws the current menu
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Menu::Draw()
{
	CClear(m_current->m_background);

	for (int i = 0; i < m_current->m_buttons.Length(); ++i)
		m_current->m_buttons[i].Draw();
}


/************************************************************************
* Purpose: Ensures that all buttons are the same width
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Menu::ResizeButtons()
{
	int largest = m_buttons[0].Width();
	for (int i = 1; i < m_buttons.Length(); ++i)
	{
		if (m_buttons[i].Width() > largest)
			largest = m_buttons[i].Width();
	}

	int height = 0;
	for (int i = 0; i < m_buttons.Length(); ++i)
	{
		m_buttons[i].Resize(largest, m_buttons[i].Height());
		m_buttons[i].SetPos((m_x - m_buttons[i].Width() / 2), (m_y + height));
		height += m_buttons[i].Height() + 1;
	}
}
