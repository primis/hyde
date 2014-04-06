// hyde.h -- Header file for the windowing engine

#ifndef __HYDE_H
#define __HYDE_H

enum ElementTypes {
	TEXTBOX,
	CHECKBOX,
	RADIOBUTTON,
	BUTTON,
	INPUTBOX,
	SECUREINPUT,
	TEXT,
	HLINE,
	VLINE,
	HSCROLLER,
	VSCROLLER,
	COMBOBOX,
	STEPPER,
	PROGRESSBAR,
	CELLROW,
	LIST
};
enum PanelTypes {
	NORMAL,
	TABBED,
	SCROLLABLE,
	TABLE,
	MENU
};

typedef void (*callback_t)(void);

typedef struct {
	int x;
	int y;
	int width;
	int height;
} location;

typedef struct elementNodeStruct {
	struct elementStruct *E;
	struct elementNodeStruct *next;
} elementNode;

typedef struct elementStruct {
	int GUID;
	int type;
	int value;
	char *string;
	location *L;
	callback_t callback;
	char* meta;
	elementNode *elements;
} element;

typedef struct panelNodeStruct {
	struct panelStruct *P;
	struct panelNodeStruct *next;
} panelNode;

typedef struct panelStruct {
	int GUID;
	int visible;
	int type;
	char *string;
	location *L;
	elementNode *elements;
	panelNode *panels;
} panel;



///////////////////////// Constructors /////////////////////////////////

location *Location(int x, int y, int width, int height);

panel *Panel(int type, location *L);
panelNode *PanelNode(panel *P, panelNode *next);

element *Element(int type, location *L);
elementNode *ElementNode(element *E, elementNode* next);

panel *Window(char* name, location *L);

#endif
