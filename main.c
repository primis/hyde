// 2014 Nick Sargente
// Hyde - Dual Personality Windowing engine.

#include <stdio.h>
#include "Include/hyde.h"

int main()
{
	panel* Win;
	Win = Window("Test", Location(100,100,400,400));
	Win->visible = 1;
	return 0;
}
