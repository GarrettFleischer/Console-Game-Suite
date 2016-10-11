/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Console.cpp
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#include "Model.h"
#include "View.h"
#include "ListIterator.h"

Model::Model()
{}

Model::Model(const Model & copy)
	: m_views(copy.m_views)
{}

Model::~Model()
{}

Model & Model::operator=(const Model & rhs)
{
	if (this != &rhs)
		m_views = rhs.m_views;

	return *this;
}

void Model::Register(View & view)
{
	try	{ m_views.Extract(&view); }	catch(const Exception &) {}
	m_views.Append(&view);
}

void Model::Remove(View & view)
{
	try { m_views.Extract(&view); }	catch (const Exception &) {}
}

void Model::Notify()
{
	for (ListIterator<View *> iter(&m_views); !iter.IsDone(); iter.MoveNext())
		iter.GetCurrent()->ModelUpdated();
}
