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

void TooSmall(Window win, GC gc, XFontStruct *font_info) {
	char * string1 = "Too Small";
	int y_offset, x_offset;
	y_offset = font_info->ascent +2;
	x_offset = 2;

	//Output text on each line.
	XDrawString(display, win, gc, x_offset, y_offset, string1,
		strlen(string1));
}

void place_graphics(Window win, GC gc, unsigned int window_width,
	unsigned int window_height) {
	int x,y;
	int width, height;
	height = window_height/2;
	width = 3 * window_width/4;
	x = window_width/2 - width/2;
	y = window_height/2 - height/2;
	XDrawRectangle(display, win, gc, x, y, width, height);
}

void place_text(Window win, GC gc, XFontStruct *font_info,
	unsigned int win_width, unsigned int win_height) {

	char *string1 = "Hello, World!";
	int len1 = strlen(string1);
	XDrawString(display, win, gc, 20, 20, string1, len1);
}

void GetGC(Window win, GC *gc, XFontStruct *fontInfo) {
	unsigned long valuemask  = 0; // Ignore XCGValues

	XGCValues values;
	unsigned int line_width = 3;
	int line_style = LineSolid;
	int cap_style = CapRound;
	int join_style = JoinMiter;
	int dash_offset = 0;
	static char dash_list[] = {1,2};
	int list_length = 2;

	// Create Graphics Context

	*gc = XCreateGC(display, win, valuemask, &values);

	//Font
	XSetFont(display, *gc, fontInfo->fid);
	XSetForeground(display, *gc, BlackPixel(display,screenNum));
	XSetLineAttributes(display, *gc, line_width, line_style, cap_style,
		join_style);
	XSetDashes(display, *gc, dash_offset, dash_list, list_length);
}

void load_font(XFontStruct **font_info) {
	char *fontname = "9x15";
	if ((*font_info = XLoadQueryFont(display,fontname)) == NULL) {
		(void) fprintf(stderr, "Cannot open font!\n");
		exit(-1);
	}
}

void renderWindows()
{

	hPanel *Current = RootWindows->P;
	Window win;
	unsigned int width, height;
	int x=0, y=0;
	unsigned borderWidth = 4;
	char *window_name = Current->string;
	XSizeHints *sizeHints;
	XWMHints *wmHints;
	XClassHint *classHint;
	XTextProperty windowName;
	XEvent report;
	GC gc;
	XFontStruct *fontInfo;
	char *displayName = NULL;
	int windowSize = 0;
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
	width 	= Current->L->width;
	height 	= Current->L->height;

	// Create an Opaque Window
	win = XCreateSimpleWindow(display, RootWindow(display, screenNum),
			x, y, width, height, borderWidth, BlackPixel(display,
			screenNum), WhitePixel(display, screenNum));
	sizeHints->flags = PPosition | PSize | PMinSize;
	sizeHints->min_width = 300;
	sizeHints->min_height = 200;
	if (XStringListToTextProperty(&window_name, 1, &windowName) == 0) {
		(void) fprintf(stderr, "Structure Allocation Failure\n");
		exit(-1);
	}
	wmHints->initial_state 	= NormalState;
	wmHints->input			= True;
	wmHints->flags = StateHint | InputHint;
	classHint->res_name = progName;
	classHint->res_class = "TestWin";
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

	while(1) {
		XNextEvent(display, &report);
		switch (report.type) {
		case Expose: // Don't redraw until last contigous expose
			if(report.xexpose.count != 0)
				break;
			if (windowSize == 0)
				TooSmall(win, gc, fontInfo);
			else {
				place_text(win, gc, fontInfo, width, height);
				place_graphics(win, gc, width, height);
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
		case ButtonPress: // Go Straight on to keypress, no break
		case KeyPress:
			XUnloadFont(display, fontInfo->fid);
			XFreeGC(display, gc);
			XCloseDisplay(display);
			exit(1);
		default:		// Throw most of the other garbage out.
			break;
		} // End Switch
	} // End While Loop
}
