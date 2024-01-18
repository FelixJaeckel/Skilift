#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int gotoxy(HANDLE, unsigned short, unsigned short);

int main(int argc, char *argv[]) {
	
	int zehnerkarten, bergstation_lift, tageskarten;
	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer gotoxy() benoetigt */
	
	zehnerkarten = 15;
	bergstation_lift = 2;
	tageskarten = 51;
	
	while(1)
	{
		printf("10er-Karten:  %i                                   ___Bergstation    Lift ab:  %i\n"
				"Tageskarten:  %i                                  /        |    |\n"
				"Skifahrten:   77                                 /        /     |\n"
				"                                                -        /      |\n"
				"                                               /        |       |\n"
				"Lift M<>B:  22                               B2:  6   R2:   8  /\n"
				"                                             /        /       /\n"
				"                                         ----        |       /\n"
				"                                        /           /       /       Lift auf:  1\n"
				"                                        Mittelstation      |\n"
				"                                   _____Bistro:  7        /         Lift ab:   0\n"
				"                                  /       \\             |\n"
				"                                  \\        |           /\n"
				"Lift T<>M:  14                   B1:  4    R1: 12     S1:  5\n"
				"                                   \\        \\        /\n"
				"                                    \\       /       /\n"
				"                                     ----Talstation--               Lift auf:  2\n"
				"10:12 Uhr                               (H):  0\n"
				"Personen auf Berg:  83                  [P]:  1 Auto\n"
				"...(T)urbo\n"
				"...(P)ause"                                                
				, zehnerkarten, bergstation_lift, tageskarten);
		
		
		zehnerkarten++;
		bergstation_lift++;
		tageskarten++;
		gotoxy(hStdout, 0,0); /* setzt Cursor an den Anfang */
		Sleep(1200);
	}
	
	return 0;
}

/* setzt cursor zu angegebenen Koordinaten, in diesem Programm nur zu (0,0), also an den Anfang, damit es so wirkt, als ob nur die Zahlenwerte sich veraendern */
int gotoxy(HANDLE hStdout, unsigned short x, unsigned short y)
{
   return SetConsoleCursorPosition(hStdout, (COORD){x,y});
}