// 2014 Nick Sargente
// Hyde - Dual Personality Windowing engine.


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Include/hyde.h"
extern void renderWindows();
extern int HYDE;
int main(int argv, char** argc)
{
	if(argv == 2){
		if(strcmp(argc[1], "hyde") == 0) {
			HYDE = 1;
		} else if (strcmp(argc[1], "jekyll") == 0) {
			HYDE = 0;
		} else {
			printf("%s -- Arguments \nhyde - Launch x11\njekyll - Launch Terminally\n", argc[0]);
		}
	} else {
		printf("%s -- Arguments \nhyde - Launch x11\njekyll - Launch Terminally\n", argc[0]);
		exit(0);
	}
	hWindow* Win;
	Win = HWindow("Hello, World!", HLocation(200,300,400,300));
	Win->visible = 1;

	hElement* TestText;
	TestText = HElement(TEXT, HLocation(10, 15, 0,0));
	TestText->string = "This is Text";
	Win->elements = HElementNode(TestText, Win->elements);

	TestText = HElement(INPUTBOX, HLocation(10, 40,40,3));
	TestText->string = "This is a Input Box";
	Win->elements = HElementNode(TestText, Win->elements);

	TestText = HElement(BUTTON, HLocation(10, 70, 0,0));
	TestText->string = "This is a Button";
	Win->elements = HElementNode(TestText, Win->elements);

	TestText = HElement(CHECKBOX, HLocation(20, 95, 0,0));
	TestText->value = 1; TestText->string = "X";
	Win->elements = HElementNode(TestText, Win->elements);


	TestText = HElement(HLINE, HLocation(10, 150, 390,0));
	Win->elements = HElementNode(TestText, Win->elements);

	TestText = HElement(SECUREINPUT, HLocation(10, 120,40,3));
	TestText->string = "This is a Input Box";
	Win->elements = HElementNode(TestText, Win->elements);

	hInit();
	while(1)
		hPoll();

	return 0;
}

