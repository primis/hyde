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

typedef struct locationStruct {
	int X;
	int Y;
	int Xsize;
	int Ysize;
} location;

typedef struct elementStruct {
	int GUID;
	int type;
	int value;
	char *string;
	location L;
	char *meta;
	callback_t callback;
	struct elementListStruct *elements;
} element;

typedef struct elementListStruct {
	struct elementStruct		E;
	struct elementListStruct	*next;
} elementList;

typedef struct panelStruct {
	int GUID;
	int type;
	char *string;
	elementList elements;
	struct panelListStruct *panels;
} panel;
typedef struct panelListStruct{
	struct  panelStruct		P;
	struct panelListStruct *next;
} panelList;


#endif
