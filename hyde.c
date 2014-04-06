// X11 Includes
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

// Standard Includes
#include "Include/hyde.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

extern hPanelNode *RootWindows;
static char *progName;
Display *display;
int screenNum;

/**********************************************************************/
//                       Actual X11 Code                              //
/**********************************************************************/

void place_graphics(Window win, GC gc, hElementNode *Element) {

	while(Element->E != NULL)
	{
		switch(Element->E->type) {
		case SECUREINPUT:
		case INPUTBOX:
			XDrawRectangle(display, win, gc,
				Element->E->L->x,
				Element->E->L->y-13,
				Element->E->L->width*9+7,
				15
			);
			break;
		case TEXTBOX:
			XDrawRectangle(display, win, gc,
				Element->E->L->x,
				Element->E->L->y-13,
				Element->E->L->width*9,
				Element->E->L->height*16
				);
				break;
		case HLINE:
			XDrawLine(display, win, gc,
				Element->E->L->x,
				Element->E->L->y,
				Element->E->L->width,
				Element->E->L->y
			);
			break;
		case VLINE:
			XDrawLine(display, win, gc,
				Element->E->L->x,
				Element->E->L->y,
				Element->E->L->x,
				Element->E->L->height
			);
			break;
		case CHECKBOX:
			XDrawRectangle(display, win, gc,
				Element->E->L->x+1,
				Element->E->L->y-13,
				13,
				13
			);
			XDrawLine(display, win, gc,
				Element->E->L->x+1,
				Element->E->L->y+1,
				Element->E->L->x + (strlen(Element->E->string)*9+5),
				Element->E->L->y+1
			);
			XDrawLine(display, win, gc,
				Element->E->L->x+2,
				Element->E->L->y+2,
				Element->E->L->x + (strlen(Element->E->string)*9+6),
				Element->E->L->y+2
			);
			XDrawLine(display, win, gc,
				Element->E->L->x + (strlen(Element->E->string)*9+6),
				Element->E->L->y-12,
				Element->E->L->x + (strlen(Element->E->string)*9+6),
				Element->E->L->y +2
			);
			break;
		case BUTTON:
			XDrawRectangle(display, win, gc,
				Element->E->L->x,
				Element->E->L->y-15,
				(strlen(Element->E->string)*9+18),
				18
			);
			XDrawLine(display, win, gc,
				Element->E->L->x+1,
				Element->E->L->y+4,
				Element->E->L->x + (strlen(Element->E->string)*9+19),
				Element->E->L->y+4
			);
			XDrawLine(display, win, gc,
				Element->E->L->x+2,
				Element->E->L->y+5,
				Element->E->L->x + (strlen(Element->E->string)*9+20),
				Element->E->L->y+5
			);
			XDrawLine(display, win, gc,
				Element->E->L->x + (strlen(Element->E->string)*9+19),
				Element->E->L->y-14,
				Element->E->L->x + (strlen(Element->E->string)*9+19),
				Element->E->L->y+5
			);
			XDrawLine(display, win, gc,
				Element->E->L->x + (strlen(Element->E->string)*9+20),
				Element->E->L->y-13,
				Element->E->L->x + (strlen(Element->E->string)*9+20),
				Element->E->L->y+5
			);
			break;
		}
		Element = Element->next;
	}
}

void place_text(Window win, GC gc, hElementNode *Element) {
	while(Element->E != NULL)
	{
		if(Element->E->string)
		{
			int temp;
			char *tempString;

			switch(Element->E->type) {
				case SECUREINPUT:
					tempString = (char*)malloc(sizeof(Element->E->string));
					memset(tempString, '*', strlen(Element->E->string));
					temp = Element->E->L->width;
					if(strlen(Element->E->string) > temp) {
						XDrawString(display, win, gc, Element->E->L->x+4,
						Element->E->L->y,
						tempString + (strlen(Element->E->string-temp)),
						strlen(Element->E->string)
						);
					} else {
						XDrawString(display, win, gc,
						Element->E->L->x + (temp-strlen(Element->E->string))*9,
						Element->E->L->y,
						tempString,
						strlen(Element->E->string)
						);
					}
					free(tempString);
					break;
				case TEXT:
				XDrawString(display, win, gc, Element->E->L->x,
					Element->E->L->y, Element->E->string,
					strlen(Element->E->string));
					break;
				case BUTTON:
				XDrawString(display, win, gc, Element->E->L->x+8,
					Element->E->L->y, Element->E->string,
					strlen(Element->E->string));
					break;
				case CHECKBOX:
					if(Element->E->value == 1)
						XDrawString(display, win, gc, Element->E->L->x+3,
					Element->E->L->y, Element->E->string,
					strlen(Element->E->string));
					break;
				case INPUTBOX:
					temp = Element->E->L->width;
					if(strlen(Element->E->string) > temp) {
						XDrawString(display, win, gc, Element->E->L->x+4,
						Element->E->L->y,
						Element->E->string + (strlen(Element->E->string-temp)),
						strlen(Element->E->string)
						);
					} else {
						XDrawString(display, win, gc,
						Element->E->L->x + (temp-strlen(Element->E->string))*9,
						Element->E->L->y,
						Element->E->string,
						strlen(Element->E->string)
						);
					}
					break;
				default:
				XDrawString(display, win, gc, Element->E->L->x+4,
					Element->E->L->y, Element->E->string,
					strlen(Element->E->string));
					break;
			}
		}
		Element = Element->next;
	}
}

void GetGC(Window win, GC *gc, XFontStruct *fontInfo) {
	unsigned long valuemask  = 0; // Ignore XCGValues

	XGCValues values;
	unsigned int line_width = 1;
	int line_style = LineSolid;
	int cap_style = CapRound;
	int join_style = JoinMiter;

	// Create Graphics Context

	*gc = XCreateGC(display, win, valuemask, &values);

	//Font
	XSetFont(display, *gc, fontInfo->fid);
	XSetForeground(display, *gc, BlackPixel(display,screenNum));
	XSetLineAttributes(display, *gc, line_width, line_style, cap_style,
		join_style);
}

void load_font(XFontStruct **font_info) {
	char *fontname = "9x15";
	if ((*font_info = XLoadQueryFont(display,fontname)) == NULL) {
		(void) fprintf(stderr, "Cannot open font!\n");
		exit(-1);
	}
}

GC gc;
XSizeHints *sizeHints;
XWMHints *wmHints;
XClassHint *classHint;
XTextProperty windowName;
XFontStruct *fontInfo;
Window win;

int windowSize;

void HydeListener() {
	unsigned int width, height;
	XEvent report;
	hPanel *Current = RootWindows->P;

	width 	= Current->L->width;
	height 	= Current->L->height;


	XNextEvent(display, &report);
	switch (report.type) {
	case Expose: // Don't redraw until last contigous expose
		if(report.xexpose.count != 0)
			break;
		else {
			place_text(win, gc, Current->elements);
			place_graphics(win, gc, Current->elements);
		}
		break;
	case ConfigureNotify: // Window Has Been Resized
		width = report.xconfigure.width;
		height = report.xconfigure.height;
		if ((width < sizeHints->min_width) ||
			(height < sizeHints->min_height))
			windowSize = 0;
		else
			windowSize = 1;
		break;
	case ButtonPress:
		Current->elements->E->type=TEXT;
		redraw();
		break;
	case KeyPress:
		XUnloadFont(display, fontInfo->fid);
		XFreeGC(display, gc);
		XCloseDisplay(display);
		exit(1);
	default:		// Throw most of the other garbage out.
		break;
	} // End Switch
}


void HydeInit()
{
	hPanel *Current = RootWindows->P;
	int x=0, y=0;
	unsigned borderWidth = 4;
	char *window_name = Current->string;

	char *displayName = NULL;
	windowSize = 0;
	if (!(sizeHints = XAllocSizeHints())) {
		fprintf(stderr, "%s: Failed to allocate memory!\n", progName);
		exit(0);
	}
	if (!(wmHints = XAllocWMHints())) {
		fprintf(stderr, "%s: Failed to allocate memory!\n", progName);
		exit(0);
	}
	if (!(classHint = XAllocClassHint())) {
		fprintf(stderr, "%s: Failed to allocate memory!\n", progName);
		exit(0);
	}

	// Connect to X Server

	if ((display=XOpenDisplay(displayName))==NULL) {
		fprintf(stderr, "%s: Failed to Reach XServer %s\n",
				progName, XDisplayName(displayName));
		exit(-1);
	}

	screenNum = DefaultScreen(display);

	x 		= Current->L->x;
	y		= Current->L->y;


	// Create an Opaque Window
	win = XCreateSimpleWindow(display, RootWindow(display, screenNum),
			x, y, Current->L->width, Current->L->height,
			borderWidth, BlackPixel(display,
			screenNum), WhitePixel(display, screenNum));
	sizeHints->flags = PPosition | PSize | PMinSize;
	sizeHints->min_width = 100;
	sizeHints->min_height = 100;
	if (XStringListToTextProperty(&window_name, 1, &windowName) == 0) {
		(void) fprintf(stderr, "Structure Allocation Failure\n");
		exit(-1);
	}
	wmHints->initial_state 	= NormalState;
	wmHints->input			= True;
	wmHints->flags = StateHint | InputHint;
	classHint->res_name = Current->string;
	classHint->res_class = Current->string;
	XSetWMProperties(display, win, &windowName,NULL,NULL,0,sizeHints,
		wmHints, classHint);
	XSelectInput(display, win, ExposureMask | KeyPressMask |
		ButtonPressMask | StructureNotifyMask);
	load_font(&fontInfo);

	// Create GC for Text and Drawing
	GetGC(win, &gc, fontInfo);
	// Display Window
	XMapWindow(display, win);
	/// Main Loop
}
