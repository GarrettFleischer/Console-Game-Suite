#include "ButtonGroup.h"


ButtonGroup::ButtonGroup(int x, int y, int width, int height, bool vertical)
	: m_x(x), m_y(y), m_width(width), m_height(height), m_vertical(vertical), m_bWidth(0)
{
}


ButtonGroup::~ButtonGroup()
{}

void ButtonGroup::Update()
{
	for (int i = 0; i < m_buttons.Length(); ++i)
		m_buttons[i].Update();
}

void ButtonGroup::AddButton(Button & button)
{

}

//Button & ButtonGroup::Clicked(Mouse::BUTTON btn)
//{
//
//	return void;
//}
