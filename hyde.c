// X11 Implementation

#include "Include/hyde.h"
#include <malloc.h>

panelNode *RootWindows;
int CurrentGUID;

int genGUID()
{
	return ++CurrentGUID;
}

// These are all the init functions, since we're not in C++, these are
// All Discrete functions. I kinda like it this way anyways.

panel *Panel(int type, location *L)
{
	panel *temp = (panel*)malloc(sizeof(panel));

	temp->type = type;
	temp->GUID = genGUID();
	temp->L = L;
	temp->visible = 1;

	temp->panels = (panelNode*)malloc(sizeof(panelNode));
	temp->elements = (struct elementNodeStruct*)malloc(sizeof(elementNode));


	temp->string 		= (char*)0;
	temp->panels->next 	= (panelNode*)0;
	temp->panels->P 	= (panel*)0;
	temp->elements->E 	= (element*)0;
	temp->elements->next	= (struct elementNodeStruct*)0;

	return temp;
}

location *Location(int x, int y, int width, int height)
{
	location *temp = (location*)malloc(sizeof(location));

	temp->x 		= x;
	temp->y 		= y;
	temp->width		= width;
	temp->height	= height;

	return temp;
}

panelNode *PanelNode(panel *P, panelNode *next)
{
	panelNode *temp = (panelNode*)malloc(sizeof(panelNode));

	temp->P 	= P;
	temp->next	= next;

	return temp;
}

element *Element(int type, location *L)
{
	element *temp = (element*)malloc(sizeof(element));

	temp->GUID 		= genGUID();
	temp->type 		= type;
	temp->L 		= L;

	temp->callback	= 0;
	temp->meta		= (char*)0;
	temp->elements 	= (elementNode*)0;
	temp->string	= (char*)0;
	temp->value		= 0;

	return temp;
}

elementNode *ElementNode(element *E, elementNode *next)
{
	elementNode *temp = (elementNode*)malloc(sizeof(elementNode));

	temp->E = E;
	temp->next = next;

	return temp;
}

panel *Window(char* name, location *L)
{
	panel *temp = Panel(NORMAL, L);

	temp->string = name;
	temp->visible = 0;
	RootWindows = PanelNode(temp, RootWindows);

	return temp;
}

////////////////////////////////////////////////////////////////////////
/////////////////////// End of Constructors ////////////////////////////
////////////////////////////////////////////////////////////////////////
