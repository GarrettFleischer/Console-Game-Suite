/************************************************************************
* Author:		Garrett Fleischer
* Filename:		crtdbg_new.h
* Date Created:	1/17/16
* Modifications: N/A
*************************************************************************/

#ifndef CRTDBG_NEW_H
#define CRTDBG_NEW_H

#include <crtdbg.h> 


/************************************************************************
* Purpose: To setup the memory leak checker
*
* Usage: Include this file in every class you wish to check for memory leaks
*			It will display the file name and line number of the "new" that caused
*			the leak
*
*************************************************************************/
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

#endif // CRTDBG_NEW_H