// ncurses Implementation

#include <ncurses.h>
#include <string.h>
#include <malloc.h>

#include "Include/hyde.h"

extern hPanelNode *RootWindows;

hElementNode *currentUIX;

void JekyllInit()
{
	initscr();
	refresh();
	noecho();
	currentUIX = RootWindows->P->elements;
}

void type_graphics()
{
	hElementNode *Element = RootWindows->P->elements;
	while(Element->E != NULL)
	{
		int temp;
		char *tempString;
		switch(Element->E->type) {
		case HLINE:
			tempString = (char*)malloc(Element->E->L->width/9);
			memset(tempString, '=', Element->E->L->width/9);
			mvprintw(Element->E->L->y/15,
			Element->E->L->x/9,
			tempString);
			free(tempString);
			break;
		case VLINE:
			for(temp = 0; temp < Element->E->L->height/16; temp++)
				mvprintw(Element->E->L->y/15+temp,
				Element->E->L->x/9,
				"|");
			break;
		default:
			break;
		}
		Element = Element->next;
	}
	refresh();
}

void type_text()
{
	hElementNode *Element = RootWindows->P->elements;
	while(Element->E != NULL)
	{
		if(Element->E->string)
		{
			int temp;
			char *tempString;

			switch(Element->E->type) {
				case SECUREINPUT:
				attron(A_UNDERLINE);
				tempString = (char*)malloc(sizeof(Element->E->string));
					memset(tempString, '*', strlen(Element->E->string));
					temp = Element->E->L->width;
					if(strlen(Element->E->string) > temp) {
						mvprintw(Element->E->L->y/15,
						Element->E->L->x/9,
						tempString + (strlen(Element->E->string-temp)));
					} else {
						mvprintw(Element->E->L->y,
							Element->E->L->x + (temp-strlen(Element->E->string)),
							tempString
							);
					}
					attroff(A_UNDERLINE);
					free(tempString);
					break;
				case TEXT:
					mvprintw(Element->E->L->y/15, Element->E->L->x/9,
						Element->E->string
					);
					break;
				case BUTTON:
					tempString = (char*)malloc(strlen(Element->E->string)+2);
					strcpy(tempString, "[");
					strcat(tempString, Element->E->string);
					strcat(tempString, "]");

					mvprintw(Element->E->L->y/15, Element->E->L->x/9,
						tempString
					);
					break;
				case CHECKBOX:
					if(Element->E->value == 1)
					mvprintw(Element->E->L->y/15,
						Element->E->L->x/9,
						"[X]");
					else
						mvprintw(Element->E->L->y/15,
						Element->E->L->x/9,
						"[ ]"
					);
					break;
				case INPUTBOX:
					attron(A_UNDERLINE);
					temp = Element->E->L->width/9;
					if(strlen(Element->E->string) > temp) {
						mvprintw(Element->E->L->y/16, Element->E->L->x/9,
						Element->E->string + (strlen(Element->E->string-temp)));
					} else {
						mvprintw(Element->E->L->y,
							Element->E->L->x/9 + (temp-strlen(Element->E->string)),
							Element->E->string
							);
					}
					attroff(A_UNDERLINE);
					break;
				default:
					mvprintw(Element->E->L->y/16, Element->E->L->x/9,
						Element->E->string);
					break;
			}
		}
		Element = Element->next;
	}
	refresh();
}

void JeckyllRepaint()
{
	type_text();
	type_graphics();
}

void JeckyllListener()
{
	JeckyllRepaint();
	//int ch = getchar();

}
