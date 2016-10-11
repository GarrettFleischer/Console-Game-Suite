/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Button.cpp
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#include "Button.h"

///////////////////////////////////////////////////////////////
//	CTORS AND DTOR
//////

Button::Button(int x, int y, int id, const string & text, COLOR background, COLOR foreground, COLOR background_hover, COLOR foreground_hover)
	: m_x(x), m_y(y), m_id(id), m_text(text),
	m_background(background), m_foreground(foreground), m_backgroundHover(background_hover), m_foregroundHover(foreground_hover),
	m_hover(false), m_clicked(3), m_height(3)
{
	m_width = m_text.length() + 2;

	m_clicked[Mouse::LEFT] = false;
	m_clicked[Mouse::MIDDLE] = false;
	m_clicked[Mouse::RIGHT] = false;
}

Button::Button(const Button & copy)
{
	*this = copy;
}

Button::~Button()
{}

//////
//	END CTORS AND DTOR
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	OPERATORS
//////

Button & Button::operator=(const Button & rhs)
{
	m_id = rhs.m_id;
	m_text = rhs.m_text;
	m_background = rhs.m_background;
	m_backgroundHover = rhs.m_backgroundHover;
	m_foreground = rhs.m_foreground;
	m_foregroundHover = rhs.m_foregroundHover;

	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_width = rhs.m_width;
	m_height = rhs.m_height;

	return *this;
}

//////
//	END OPERATORS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PUBLIC METHODS
//////

/************************************************************************
* Purpose: To detect hover / click events on this button and redraw if necessary
*
* Precondition:
*		Assumes that Mouse::UpdateMouseState() has already been called
*
* Postcondition:
*		Modifies:	Hover/Click state, and the console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Button::Update()
{
	int mx = Mouse::X(),
		my = Mouse::Y();

	bool hover = ((mx >= m_x && mx < m_x + m_width) && (my >= m_y && my < m_y + m_height));

	m_clicked[Mouse::LEFT] = (hover && Mouse::BtnPressed(Mouse::LEFT));
	m_clicked[Mouse::MIDDLE] = (hover && Mouse::BtnPressed(Mouse::MIDDLE));
	m_clicked[Mouse::RIGHT] = (hover && Mouse::BtnPressed(Mouse::RIGHT));

	if (m_hover != hover)
	{
		m_hover = hover;
		Draw();
	}
}

/************************************************************************
* Purpose: To draw this button to the screen
*
* Precondition:
*
* Postcondition:
*		Modifies:	The console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Button::Draw()
{
	COLOR foreground = (m_hover ? m_foregroundHover : m_foreground);
	COLOR background = (m_hover ? m_backgroundHover : m_background);

	CClearRect(m_x, m_y, m_x + m_width, m_y + m_height, CMakeBackground(background));

	char * str = TrimText();
	CWrite(m_x + m_width / 2 - strlen(str) / 2, m_y + m_height / 2, str, CMakeColor(foreground, background));

	delete[] str;
}

//////
//	END PUBLIC METHODS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	GETTERS AND SETTERS
//////

int Button::ID() const
{
	return m_id;
}

const string & Button::Text() const
{
	return m_text;
}

/************************************************************************
* Purpose: To set the text on this button
*
* Precondition:
*	resize - whether or not to auto resize the button to the length of the text
*
* Postcondition:
*		Modifies:	Calls Draw()
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Button::SetText(const string & text, bool resize)
{
	m_text = text;

	if (resize)
		m_width = m_text.length() + 2;

	Draw();
}

/************************************************************************
* Purpose: To change the default and hover colors of this button
*
* Precondition:
*
* Postcondition:
*		Modifies:	Calls Draw()
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Button::SetColors(COLOR background, COLOR foreground, COLOR background_hover, COLOR foreground_hover, bool draw)
{
	m_background = background;
	m_foreground = foreground;

	m_backgroundHover = background_hover;
	m_foregroundHover = foreground_hover;

	if(draw)
		Draw();
}

int Button::X() const
{
	return m_x;
}

int Button::Y() const
{
	return m_y;
}

int Button::Width() const
{
	return m_width;
}

int Button::Height() const
{
	return m_height;
}

/************************************************************************
* Purpose: To move this button to another location on the screen
*
* Precondition:
*
* Postcondition:
*		Modifies:	Clears the region currently occupied by the button with the specified background color
*					Moves to the new position
*					Calls Draw()
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Button::SetPos(int x, int y, COLOR background, bool clear)
{
	if(clear)
		CClearRect(m_x, m_y, m_x + m_width, m_y + m_height, CMakeBackground(background));

	m_x = x;
	m_y = y;
	//Draw();
}

/************************************************************************
* Purpose: To change the width and height of this button
*
* Precondition:
*		width - Must be non-negative
*		height - Must be non-negative
*
* Postcondition:
*		Modifies:	Clears the region currently occupied by the button with the specified background color
*					Resizes the button
*					Calls Draw()
*		Throws:	Exception("Button width must be non-negative!")
				Exception("Button height must be non-negative!")
*		Returns:	N/A
*************************************************************************/
void Button::Resize(int width, int height, COLOR background)
{
	if (width < 0)
		throw Exception("Button width must be non-negative!");
	else if (height < 0)
		throw Exception("Button height must be non-negative!");
	else
	{
		if (width < m_width || height < m_height)
			CClearRect(m_x, m_y, m_x + m_width, m_y + m_height, CMakeBackground(background));

		m_width = width;
		m_height = height;

		Draw();
	}
}


/************************************************************************
* Purpose: To determine if this button was clicked by the specified mouse button
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if this button was clicked by the specified mouse button
*************************************************************************/
bool Button::Clicked(Mouse::BUTTON btn) const
{
	return m_clicked[btn];
}

/************************************************************************
* Purpose: To determine if this button was hovered over by the mouse
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	TRUE if this button was hovered over by the mouse
*************************************************************************/
bool Button::Hovered() const
{
	return m_hover;
}

//////
//	END GETTERS AND SETTERS
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//	PRIVATE METHODS
//////

/************************************************************************
* Purpose: To ensure that the text fits inside the bounds of this button
*
* Precondition:
*
* Postcondition:
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	A pointer to a cstring that fits within the bounds of this button
*************************************************************************/
char * Button::TrimText()
{
	char * str = nullptr;

	if (m_width > 0)
	{
		if (int(m_text.length()) >= m_width - (2 * (m_width > 2)))
		{
			str = new char[m_width - 1];
			for (int i = 0; i < m_width - 1; ++i)
				str[i] = m_text.c_str()[i];

			str[max(0, m_width - 2)] = '\0';
		}
		else
		{
			str = new char[m_text.length() + 1];
			strcpy(str, m_text.c_str());
		}
	}
	else
	{
		str = new char[1];
		str[0] = '\0';
	}

	return str;
}

//////
//	END PRIVATE METHODS
///////////////////////////////////////////////////////////////