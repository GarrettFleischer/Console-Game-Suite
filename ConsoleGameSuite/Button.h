/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Button.h
* Date Created:	1/15/16
* Modifications: N/A
*************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
using std::string;

#include "Console.h"
#include "Mouse.h"

#include "Exception.h"

/************************************************************************
* Class: Button
*
* Purpose: This class creates a simple push button and draws it on the console window
*
* Manager functions:
*	Button(x, y, id, text, background, foreground, background_hover, foreground_hover)
*		Draw is not called automatically
*
*	Button(const Button & copy)
*	operator=(const Button & rhs)
*
*	~Button()
*
* Methods:
*	Update()
*		Handle mouse events and redraw if necessary
*
*	Draw()
*		Draw the button on the screen
*
*************************************************************************/
class Button
{
public:
	// CTORS AND DTOR
	Button(int x = 0, int y = 0, int id = 0, const string & text = "",
		COLOR background = Color::white, COLOR foreground = Color::black,
		COLOR background_hover = Color::bright_white, COLOR foreground_hover = Color::grey);

	Button(const Button & copy);

	virtual ~Button();

	// OPERATORS
	Button & operator=(const Button & rhs);

	// METHODS
	void Update();
	virtual void Draw();

	// GETTERS AND SETTERS
	int ID() const;

	const string & Text() const;
	void SetText(const string & text, bool resize = true);

	void SetColors(COLOR background = Color::white, COLOR foreground = Color::black,
		COLOR background_hover = Color::bright_white, COLOR foreground_hover = Color::grey, bool draw = true);

	int X() const;
	int Y() const;
	int Width() const;
	int Height() const;
	void SetPos(int x, int y, COLOR background = Color::black, bool clear = true);

	void Resize(int width, int height, COLOR background = Color::black);

	bool Clicked(Mouse::BUTTON btn) const;
	bool Hovered() const;

protected:
	// METHODS
	char * TrimText();

	Array<bool> m_clicked;

	int m_id;
	string m_text;
	COLOR m_background;
	COLOR m_backgroundHover;
	COLOR m_foreground;
	COLOR m_foregroundHover;

	int m_x;
	int m_y;
	int m_width;
	int m_height;

	bool m_hover;
};

#endif // BUTTON_H
