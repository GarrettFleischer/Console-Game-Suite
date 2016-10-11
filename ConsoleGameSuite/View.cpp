/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "View.h"
#include "Model.h"

View::View(Model * model)
	: m_model(model)
{
	if(m_model != nullptr)
		m_model->Register(*this);
}

View::View(const View & copy)
	: m_model(copy.m_model)
{
	if (m_model != nullptr)
		m_model->Register(*this);
}

View::~View()
{
	if (m_model)
	{
		m_model->Remove(*this);
		m_model = nullptr;
	}
}

View & View::operator=(const View & rhs)
{
	m_model = rhs.m_model;

	if (m_model)
		m_model->Register(*this);

	this->ModelUpdated();

	return *this;
}

void View::SetModel(Model * model)
{
	if(m_model)
		m_model->Remove(*this);

	m_model = model;
	if (m_model)
		m_model->Register(*this);

	this->ModelUpdated();
}

Model * View::GetModel()
{
	return m_model;
}

const Model * View::GetModel() const
{
	return m_model;
}
