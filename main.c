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
	renderWindows();
	return 0;
}
