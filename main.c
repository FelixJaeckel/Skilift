#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Uhrzeit;

int cursorSetzen(HANDLE, unsigned short, unsigned short);
void getUhrzeit(int);
void uhrzeitAusgeben(Uhrzeit);

typedef struct Uhrzeit 
{
    int stunde;
    int minute;
} Uhrzeit;

Uhrzeit uhrzeit;


int main(int argc, char *argv[]) {
	
	int zehnerkarten, bergstation_lift, tageskarten, minuten;
	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540;
	uhrzeit.stunde = 9;
	uhrzeit.minute = 0;
	
	zehnerkarten = 15;
	bergstation_lift = 2;
	tageskarten = 51;
	
	while(minuten <= 1320)
	{
		printf( "10er-Karten:  %i                                   ___Bergstation    Lift ab:  %i\n"
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
				"  :   Uhr                               (H):  0\n"
			   	"Personen auf Berg:  83                  [P]:  1 Auto\n"
				"...(T)urbo\n"
				"...(P)ause"                                                
				, zehnerkarten, bergstation_lift, tageskarten);
		
		uhrzeitAusgeben(uhrzeit);
		
		zehnerkarten++;
		bergstation_lift++;
		tageskarten++;
		
		cursorSetzen(hStdout, 0, 0); /* setzt Cursor an den Anfang */
		Sleep(1000);
		minuten++;
		getUhrzeit(minuten);
	} 
	
	return 0;
}

/* setzt cursor zu angegebenen Koordinaten */
int cursorSetzen(HANDLE hStdout, unsigned short x, unsigned short y)
{
   return SetConsoleCursorPosition(hStdout, (COORD){x,y});
}

void getUhrzeit(int minuten)
{
	uhrzeit.stunde = minuten / 60;
	uhrzeit.minute = minuten % 60;
	return;
}

void uhrzeitAusgeben(Uhrzeit uhrzeit)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	cursorSetzen(hStdout, 0, 17);
	if (uhrzeit.stunde == 9)
	{
		printf("0%i", uhrzeit.stunde);
	} 
	else 
	{
		printf("%i", uhrzeit.stunde);
	}
	
	cursorSetzen(hStdout, 3, 17);
	if (uhrzeit.minute >= 10)
	{
		printf("%i", uhrzeit.minute);
	} 
	else 
	{
		printf("0%i", uhrzeit.minute);
	} 
	return;
}