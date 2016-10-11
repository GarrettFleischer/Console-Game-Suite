#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include "Array.h"
#include "Button.h"
#include "Mouse.h"

class ButtonGroup
{
public:
	ButtonGroup(int x = 0, int y = 0, int width = -1, int height = -1, bool vertical = true);
	~ButtonGroup();

	void Update();

	void AddButton(Button & button);

	Button & Clicked(Mouse::BUTTON btn);

private:
	Array<Button> m_buttons;

	int m_x;
	int m_y;
	int m_width;
	int m_height;
	bool m_vertical;

	int m_bWidth;

};


#endif // BUTTONGROUP_H
