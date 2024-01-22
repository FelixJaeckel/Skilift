#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Uhrzeit; /* muss vor eigentlicher definition leer deklariert werden, damit der Prototyp Bescheid weiß, was eine Uhrzeit ist */

int cursorSetzen(HANDLE, unsigned short, unsigned short);
void uhrzeitAnpassen(int);
void uhrzeitAusgeben(struct Uhrzeit);

typedef struct Uhrzeit 
{
    int stunde;
    int minute;
} Uhrzeit;

Uhrzeit uhrzeit; /* uhrzeit ist globale Variable, um UhrzeitAnpassen() zu erleichtern */


int main(int argc, char *argv[]) {
	
	int zehnerkarten, bergstation_lift, tageskarten, minuten;
	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	minuten = 540; /* wir starten bei 540 Minuten, weil der Skilift 9:00 Uhr aufmacht */
	uhrzeit.stunde = 9; 
	uhrzeit.minute = 0;
	
	/* Variablen zu Testzwecken */
	zehnerkarten = 15;
	bergstation_lift = 2;
	tageskarten = 51;
	
	/* loop läuft bis 1320 Minuten, also bis 22:00 Uhr */
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
		
		uhrzeitAusgeben(uhrzeit); /* uhrzeit hat ein paar Eigenheiten, weswegen sie eine extrafunktion zum printen kriegt */
		
		/* nur zu testzwecken hier */
		zehnerkarten++;
		bergstation_lift++; 
		tageskarten++;
		
		cursorSetzen(hStdout, 0, 0); /* setzt Cursor an den Anfang, damit Ausgabe scheinbar konstant bleibt */
		Sleep(1000); /* wartet eine sekunde */
		minuten++; /* eine minute vergeht */
		uhrzeitAnpassen(minuten); /* minuten werden in uhrzeitformat umgewandelt */
	} 	
	return 0;
}


/* setzt cursor zu angegebenen Koordinaten */
int cursorSetzen(HANDLE hStdout, unsigned short x, unsigned short y)
{
   return SetConsoleCursorPosition(hStdout, (COORD){x,y});
}


/* wandelt anzahl minuten in Uhrzeit-struct bestehend aus Stunden und Minuten um */
void uhrzeitAnpassen(int minuten)
{
	uhrzeit.stunde = minuten / 60;
	uhrzeit.minute = minuten % 60;
	return;
}


/* sorgt dafür, dass uhrzeit immer mit zwei Ziffern vor und hinter dem Doppelpunkt ausgegeben wird */
void uhrzeitAusgeben(Uhrzeit uhrzeit)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); /* wird fuer cursorSetzen() benoetigt */
	
	/* packt 0 vor die Stunde wenn es um 9 ist, ansonsten wird die Stunde einfach nur geprintet */
	cursorSetzen(hStdout, 0, 17);	
	if (uhrzeit.stunde == 9) 
	{
		printf("0%i", uhrzeit.stunde);
	} 
	else 
	{
		printf("%i", uhrzeit.stunde);
	}
	
	/* packt 0 vor einstellige Minuten */
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