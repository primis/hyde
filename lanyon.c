#include "Include/hyde.h"
#include <malloc.h>

int CurrentGUID;
hPanelNode *RootWindows;

int genGUID()
{
	return ++CurrentGUID;
}

// These are all the init functions, since we're not in C++, these are
// All Discrete functions. I kinda like it this way anyways.

hPanel *HPanel(int type, hLocation *L)
{
	hPanel *temp = (hPanel*)malloc(sizeof(hPanel));

	temp->type = type;
	temp->GUID = genGUID();
	temp->L = L;
	temp->visible = 1;

	temp->panels = (hPanelNode*)malloc(sizeof(hPanelNode));
	temp->elements = (struct hElementNodeStruct*)malloc(sizeof(hElementNode));


	temp->string 		= (char*)0;
	temp->panels->next 	= (hPanelNode*)0;
	temp->panels->P 	= (hPanel*)0;
	temp->elements->E 	= (hElement*)0;
	temp->elements->next	= (struct hElementNodeStruct*)0;

	return temp;
}

hLocation *HLocation(int x, int y, int width, int height)
{
	hLocation *temp = (hLocation*)malloc(sizeof(hLocation));

	temp->x 		= x;
	temp->y 		= y;
	temp->width		= width;
	temp->height	= height;

	return temp;
}

hPanelNode *HPanelNode(hPanel *P, hPanelNode *next)
{
	hPanelNode *temp = (hPanelNode*)malloc(sizeof(hPanelNode));

	temp->P 	= P;
	temp->next	= next;

	return temp;
}

hElement *HElement(int type, hLocation *L)
{
	hElement *temp = (hElement*)malloc(sizeof(hElement));

	temp->GUID 		= genGUID();
	temp->type 		= type;
	temp->L 		= L;

	temp->callback	= 0;
	temp->meta		= (char*)0;
	temp->elements 	= (hElementNode*)0;
	temp->string	= (char*)0;
	temp->value		= 0;

	return temp;
}

hElementNode *HElementNode(hElement *E, hElementNode *next)
{
	hElementNode *temp = (hElementNode*)malloc(sizeof(hElementNode));

	temp->E = E;
	temp->next = next;

	return temp;
}

hPanel *HWindow(char* name, hLocation *L)
{
	hPanel *temp = HPanel(NORMAL, L);

	temp->string = name;
	temp->visible = 0;
	RootWindows = HPanelNode(temp, RootWindows);

	return temp;
}

////////////////////////////////////////////////////////////////////////
/////////////////////// End of Constructors ////////////////////////////
////////////////////////////////////////////////////////////////////////
extern void HydeInit();
extern void HydeListener();

void hInit()
{
	HydeInit();
}


void hPoll()
{
	HydeListener();
}
