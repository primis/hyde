// 2014 Nick Sargente
// Hyde - Dual Personality Windowing engine.

#include <stdio.h>
#include "Include/hyde.h"
extern void renderWindows();
int main()
{
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

	hInit();

	TestText = HElement(HLINE, HLocation(10, 150, 390,0));
	Win->elements = HElementNode(TestText, Win->elements);

	TestText = HElement(SECUREINPUT, HLocation(10, 120,40,3));
	TestText->string = "This is a Input Box";
	Win->elements = HElementNode(TestText, Win->elements);
	while(1)
		hPoll();

	return 0;
}

