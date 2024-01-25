#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void hidecursor();

void main()
{
	char c;
	c = NULL;
	int i;
	i = 0;
	hidecursor();
	while(i < 1000)
	{
		printf("\n%i", i);
		if (kbhit()){
			c = getche();	
		} else {
			c = "l";
		}
		
		printf("%c\n", c);
		Sleep(1);
		i = i +	100;
	}

	printf("test");

	
	
	
	
	return;
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}