/************************************************************************
* Author:		Garrett Fleischer
* Filename:		View.h
* Date Created:	2/5/16
* Modifications: N/A
*************************************************************************/
#ifndef VIEW_H
#define VIEW_H


/************************************************************************
* Class: View
*
* Purpose: This class represents a View to watch a Model
*			ModelUpdated() is called automatically when the model is modified
*
* Manager functions:
*	View();
*	View(const View & copy);
*	~View()
*	View & operator=(const View & rhs);
*
* Methods:
*
*************************************************************************/
class View
{
	friend class Model; // to access ModelUpdated()

public:
	void SetModel(Model * model);
	Model * GetModel();
	const Model * GetModel() const;

protected:
	View(Model * model = nullptr);
	View(const View & copy);

	virtual ~View();

	View & operator=(const View & rhs);

	virtual void ModelUpdated() = 0;

private:
	Model * m_model;
};

#endif // VIEW_H
