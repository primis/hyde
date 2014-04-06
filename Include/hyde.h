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
} hLocation;

typedef struct hElementNodeStruct {
	struct hElementStruct *E;
	struct hElementNodeStruct *next;
} hElementNode;

typedef struct hElementStruct {
	int GUID;
	int type;
	int value;
	char *string;
	hLocation *L;
	callback_t callback;
	char* meta;
	hElementNode *elements;
} hElement;

typedef struct hPanelNodeStruct {
	struct hPanelStruct *P;
	struct hPanelNodeStruct *next;
} hPanelNode;

typedef struct hPanelStruct {
	int GUID;
	int visible;
	int type;
	char *string;
	hLocation *L;
	hElementNode *elements;
	hPanelNode *panels;
} hPanel;

typedef hPanel hWindow;


///////////////////////// Constructors /////////////////////////////////

hLocation *HLocation(int x, int y, int width, int height);

hPanel *Panel(int type, hLocation *L);
hPanelNode *HPanelNode(hPanel *P, hPanelNode *next);

hElement *HElement(int type, hLocation *L);
hElementNode *HElementNode(hElement *E, hElementNode* next);

hWindow *HWindow(char* name, hLocation *L);

#endif
