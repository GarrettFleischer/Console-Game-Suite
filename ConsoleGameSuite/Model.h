/************************************************************************
* Author:		Garrett Fleischer
* Filename:		Model.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef MODEL_H
#define MODEL_H

#include "DoubleLinkedList.h"

class View;


/************************************************************************
* Class: Model
*
* Purpose: This class represents a Model to be connected with Views
*			When the model is updated, it Notifies all registered views
*
* Manager functions:
*	Model();
*	Model(const Model & copy);
*	~Model()
*	Model & operator=(const Model & rhs);
*
* Methods:
*
*************************************************************************/
class Model
{
public:
	virtual ~Model();

	void Register(View & view);
	void Remove(View & view);
	
protected:
	Model();
	Model(const Model & copy);

	Model & operator=(const Model & rhs);

	void Notify();

private:
	DoubleLinkedList<View *> m_views;
};

#endif // MODEL_H
